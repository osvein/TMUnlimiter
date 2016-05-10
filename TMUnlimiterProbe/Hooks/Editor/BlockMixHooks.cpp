#include "StdInc.h"

using namespace TrackMania;

namespace Hooks { namespace Editor {

    void BlockMixHooks::Init ()
    {
        static HookEntry hooks[] = {
            // Remove block placement limitations
            { Address::Inst.CTrackManiaEditor__ValidateBlockPositionAndPillars, &hook_ValidateBlockPositionAndPillars },

            // Do not remove blocks at the location where a block was just placed (except block clips)
            { Address::Inst.CTrackManiaEditor__ClearAreaForBlock_hookpos, &hook_ClearAreaForBlock },

            // Do not disconnect roads around a (non-road) block that was just placed
            { Address::Inst.CTrackManiaEditor__PlaceBlock_hookpos, Address::Inst.CTrackManiaEditor__PlaceBlock_retnpos },

            // Re-link blocks after a block was removed, so that blocks that were previously overlapped
            // become clickable again.
            // Only disconnect roads at the block's connection points, not on every unit of the block
            { Address::Inst.CTrackManiaEditor__RemoveBlock_hookpos, &hook_RemoveBlock },
            { Address::Inst.CTrackManiaEditor__RemoveBlockSafe_hookpos, &hook_RemoveBlockSafe },

            // Adjust the decision if a block is placed on the ground or not where necessary.
            // Placing a ground-only block in air or an air-only block on ground can lead to
            // unselectable blocks or crashes.
            { Address::Inst.CGameCtnChallenge__IsBlockOnGround_hookpos, &hook_IsBlockOnGround },
            { Address::Inst.CGameCtnBlockInfo__GetBlockUnitInfo, &hook_GetBlockUnitInfo },

            // Always return true from UpdateFieldUnitsForBlock to prevent out-of-build-area blocks
            // from being removed in InitBuildArea and others.
            { Address::Inst.CGameCtnChallenge__UpdateFieldUnitsForBlock_hookpos, Address::Inst.CGameCtnChallenge__UpdateFieldUnitsForBlock_retnpos },

            // Do not create clips outside the track area (will crash)
            { Address::Inst.CGameCtnChallenge__CreateBlockClip_hookpos, &hook_CreateBlockClip },

            // Do an extended block search when looking up zones. Overlapping blocks might prevent
            // the right one from being found through a direct lookup, which results in the zone
            // not being found and thus a crash.
            { Address::Inst.CGameCtnChallenge__GetZoneAtPos_hookpos, &hook_GetZoneAtPos },

            // When drawing roads, use GetBlockAtPos instead of ValidateBlockPositionAndPillars
            // for determining whether a new road block should be created or an existing one
            // reused. The Validate function always returns true with our patch, so TM would create
            // new roads all the time.
            { Address::Inst.CTrackManiaEditor__CreateRoadBlock_hookpos, &hook_CreateRoadBlock },

            // Prevent custom track area sizes stored in track.gbx from getting overriden by
            // the environment default. Load custom sizes from .ini for new tracks.
            { Address::Inst.CGameCtnChallenge__InitBuildArea_hookpos, &hook_InitBuildArea },

            // Do not snap the cursor to the ground when in terrain editing mode
            //{ Address::Inst.CTrackManiaEditorTerrain__FloorCursorPos_hookpos, &hook_FloorCursorPos },

            // Do not snap terrain block creation positions to the ground; rather, create them
            // at the cursor position.
            //{ Address::Inst.CTrackManiaEditorTerrain__CreateTerrainBlockAtPos_hookpos, &hook_CreateTerrainBlockAtPos },

            { NULL, NULL }
        };
        InstallHooks ( hooks );

        // Never destroy field units (so that block relinking doesn't write to deallocated memory!)
	    *Address::Inst.CGameCtnChallenge__RemoveBlock_hookpos = 0xEB;

	    // Do not destroy just-placed blocks if one of their clips overlaps with another block
	    // (because we want to be able to do this, and the removal also results in a crash)
	    *Address::Inst.CTrackManiaEditor__ConnectDirFromRoadBlock_hookpos = 0xEB;

	    // Allow scrolling the cursor up/down in terrain editing mode
	    //*(word *)Address::Inst.CTrackManiaEditor__ProcessKey_hookpos1 = 0x9090;
	    //*(word *)Address::Inst.CTrackManiaEditor__ProcessKey_hookpos2 = 0x9090;
	    //*(byte *)Address::Inst.CTrackManiaEditor__ProcessKey_hookpos3 = 0xEB;
	    //*(byte *)Address::Inst.CTrackManiaEditor__MoveCursorDown_hookpos = 0xEB;
    }

    _declspec(naked) void BlockMixHooks::hook_ValidateBlockPositionAndPillars ()
    {
        _asm
        {
            mov eax, 1
            retn 0x18
        }
    }

    _declspec(naked) void BlockMixHooks::hook_ClearAreaForBlock ()
    {
        _asm
        {
            push eax
                push eax
                call handle_ClearAreaForBlock
                add esp, 4

                cmp al, 0
            pop eax
            jnz cont
            jmp Address::Inst.CTrackManiaEditor__ClearAreaForBlock_skippos

cont:
            test dword ptr [eax+0x60], 0x4000
            jmp Address::Inst.CTrackManiaEditor__ClearAreaForBlock_contpos
        }
    }

    bool BlockMixHooks::handle_ClearAreaForBlock ( CGameCtnBlock* pBlock )
    {
        return pBlock->GetBlockInfo ()->GetType () == CGameCtnBlockInfo::BLOCKTYPE_CLIP;
    }

    _declspec(naked) void BlockMixHooks::hook_RemoveBlock ()
    {
        _asm
        {
            push edi
            push esi
            call handle_RemoveBlock
            add esp, 8

            cmp al, 0
            jnz cont
            jmp Address::Inst.CTrackManiaEditor__RemoveBlock_skippos

cont:
            lea ebp, dword ptr [edi+0x28]
            mov ecx, ebp
            jmp Address::Inst.CTrackManiaEditor__RemoveBlock_contpos
        }
    }

    _declspec(naked) void BlockMixHooks::hook_RemoveBlockSafe ()
    {
        _asm
        {
            push edi
            push esi
            call handle_RemoveBlock
            add esp, 8

            cmp al, 0
            jnz cont
            jmp Address::Inst.CTrackManiaEditor__RemoveBlockSafe_skippos

cont:
            mov ecx, ebp
            mov dword ptr [esp+0x58], 0
            jmp Address::Inst.CTrackManiaEditor__RemoveBlockSafe_contpos
        }
    }

    bool BlockMixHooks::handle_RemoveBlock ( CGameCtnEditor* pEditor, CGameCtnBlock* pRemovedBlock )
    {
        // Re-link blocks that were overlapped
        CGameCtnChallenge* pChallenge = pEditor->GetChallenge ();
        for ( int i = 0; i < pChallenge->NumBlocks (); i++ )
        {
            CGameCtnBlock* pBlock = pChallenge->GetBlock ( i );
            if ( !pBlock )
                continue;

            if ( pBlock->GetBlockInfo ()->GetType () == CGameCtnBlockInfo::BLOCKTYPE_FLAT ||
                pBlock->GetBlockInfo ()->GetType () == CGameCtnBlockInfo::BLOCKTYPE_FRONTIER )
                continue;

            for ( int j = 0; j < pBlock->NumBlockUnits (); j++ )
            {
                CGameCtnBlockUnit* pUnit = pBlock->GetBlockUnit ( j );
                if ( !pUnit )
                    continue;

                if ( pUnit->GetFieldUnit ()->GetBlockUnit () == NULL )
                    pUnit->GetFieldUnit ()->SetBlockUnit ( pUnit );
            }
        }

        // Only disconnect roads at the block's clip points, not everywhere (i.e. don't split up
        // roads overlapped by the block, just disconnect roads that are actually connected to it)
        if ( pRemovedBlock->GetBlockInfo ()->GetType () == CGameCtnBlockInfo::BLOCKTYPE_ROAD )
            return true;

        for ( int i = 0; i < pRemovedBlock->NumBlockUnits (); i++ )
        {
            CGameCtnBlockUnit* pUnit = pRemovedBlock->GetBlockUnit ( i );
            if ( !pUnit )
                continue;

            for ( int dir = 0; dir < 4; dir++ )
            {
                if ( pUnit->GetClipBlockInfo ( dir ) )
                    pEditor->DisconnectBlockUnitNeighbour ( pUnit, dir );
            }
        }
        return false;
    }

    _declspec(naked) void BlockMixHooks::hook_IsBlockOnGround ()
    {
        _asm
        {
            push ecx
            push dword ptr [esp+8]
            call handle_IsBlockOnGround
            add esp, 4
            pop ecx

            cmp al, 0
            jz cont

            dec eax
            retn 0x14

cont:
            sub esp, 0x20
            push ebx
            mov ebx, [esp+0x28]
            jmp Address::Inst.CGameCtnChallenge__IsBlockOnGround_retnpos;
        }
    }

    int BlockMixHooks::handle_IsBlockOnGround ( CGameCtnBlockInfo* pBlockInfo )
    {
        if ( !pBlockInfo )
            return 0;

        int numGroundUnits = pBlockInfo->GetGroundBlockUnitInfos ().Size ();
        int numAirUnits = pBlockInfo->GetAirBlockUnitInfos ().Size ();
        if ( numGroundUnits && !numAirUnits )
            return 2;
        else if ( !numGroundUnits && numAirUnits )
            return 1;
        else
            return 0;
    }

    _declspec(naked) void BlockMixHooks::hook_GetBlockUnitInfo ()
    {
        _asm
        {
            push dword ptr [esp+8]
            push dword ptr [esp+4+4]
            push ecx
            call handle_GetBlockUnitInfo
            add esp, 0xC
            retn 8
        }
    }

    void* BlockMixHooks::handle_GetBlockUnitInfo ( CGameCtnBlockInfo* pBlockInfo, int index, bool bGround )
    {
        if ( bGround && pBlockInfo->GetGroundBlockUnitInfos ().Size () == 0 )
            bGround = false;
        else if ( !bGround && pBlockInfo->GetAirBlockUnitInfos ().Size () == 0 )
            bGround = true;

        return bGround ? pBlockInfo->GetGroundBlockUnitInfos () [ index ] :
            pBlockInfo->GetAirBlockUnitInfos () [ index ];
    }

    _declspec(naked) void BlockMixHooks::hook_CreateBlockClip ()
    {
        _asm
        {
            push ecx

            push dword ptr [esp+0xC+4]
            push dword ptr [esp+0x10+8]
            push dword ptr [esp+0x14+0xC]
            push ecx
            call handle_CreateBlockClip
            add esp, 0x10

            pop ecx

            cmp al, 0
            jnz cont

            mov eax, 1
            add esp, 8
            retn 0xC

cont:
            mov eax, dword ptr fs:[0]
            jmp Address::Inst.CGameCtnChallenge__CreateBlockClip_retnpos
        }
    }

    bool BlockMixHooks::handle_CreateBlockClip ( CGameCtnChallenge* pChallenge, Vec3Di pos )
    {
        return pChallenge->IsPosInBounds ( pos );
    }

    _declspec(naked) void BlockMixHooks::hook_GetZoneAtPos ()
    {
        _asm
        {
            test eax, eax
            jz extended_search

            pop edi
            pop esi
            retn 0xC

extended_search:
            push dword ptr [esp+8+0xC]
            push dword ptr [esp+0xC+8]
            push dword ptr [esp+0x10+4]
            push esi
            call handle_GetZoneAtPos
            add esp, 0x10

            pop edi
            pop esi
            retn 0xC
        }
    }

    CGameCtnZone* BlockMixHooks::handle_GetZoneAtPos ( CGameCtnChallenge* pChallenge, Vec3Di pos )
    {
        for ( int i = 0; i < pChallenge->NumBlocks (); i++ )
        {
            CGameCtnBlock* pBlock = pChallenge->GetBlock ( i );
            if ( pBlock->OccupiesPosition ( pos ) )
            {
                CGameCtnZone* pZone = CGameCtnCollection::GetZoneByBlockInfo ( pBlock->GetBlockInfo () );
                if ( pZone )
                    return pZone;
            }
        }
        return pChallenge->GetCollection ()->GetDefaultZone ();
    }

    _declspec(naked) void BlockMixHooks::hook_CreateRoadBlock ()
    {
        _asm
        {
            add esp, 0x18

                push ebp
            push ebx
            push edi
            push esi
            call handle_CreateRoadBlock
            add esp, 0x10

            movzx eax, al
            jmp Address::Inst.CTrackManiaEditor__CreateRoadBlock_retnpos
        }
    }

    bool BlockMixHooks::handle_CreateRoadBlock ( CGameCtnEditor* pEditor, Vec3Di pos )
    {
        CGameCtnBlock* pBlock = pEditor->GetChallenge ()->GetBlockAtPos ( pos );
        return pBlock == NULL || pBlock->GetBlockInfo ()->GetType () != CGameCtnBlockInfo::BLOCKTYPE_ROAD;
    }

    _declspec(naked) void BlockMixHooks::hook_InitBuildArea ()
    {
        _asm
        {
            push esi
            call handle_InitBuildArea
            add esp, 4

            jmp Address::Inst.CGameCtnChallenge__InitBuildArea_retnpos
        }
    }

    void BlockMixHooks::handle_InitBuildArea ( CGameCtnChallenge* pChallenge )
    {
        Vec3Di vecDefaultSize = pChallenge->GetDecoration ()->GetSizeDecoration ()->GetSize ();
        Vec3Di vecBuildSize = pChallenge->GetBuildAreaSize ();
        if ( pChallenge->NumBlocks () == 0 )
        {
            // New challenge: apply custom-defined environment size default
            std::string strCustomSize = Settings::GetString ( INI_TRACKSIZES,
                pChallenge->GetCollection ()->GetEnvironmentName () );

            std::regex re ( "^\\s*(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*" );
            std::smatch match;
            if ( std::regex_search ( strCustomSize, match, re ) )
            {
                std::string strX ( match[1].first, match[1].second );
                std::string strY ( match[2].first, match[2].second );
                std::string strZ ( match[3].first, match[3].second );

                vecBuildSize.X = atoi ( strX.c_str () );
                vecBuildSize.Y = atoi ( strY.c_str () );
                vecBuildSize.Z = atoi ( strZ.c_str () );

                if ( vecBuildSize.X <= 0 || vecBuildSize.X > 256 ||
                    vecBuildSize.Y <= 0 || vecBuildSize.Y > 256 ||
                    vecBuildSize.Z <= 0 || vecBuildSize.Z > 256 )
                {
                    vecBuildSize = vecDefaultSize;
                }
            }
        }
        pChallenge->SetBuildAreaSize ( vecBuildSize );
        pChallenge->GetDecoration ()->GetSizeDecoration ()->SetSize ( vecBuildSize );
    }

    _declspec(naked) void BlockMixHooks::hook_FloorCursorPos ()
    {
        _asm
        {
            push ecx

                push dword ptr [esp+4+4]
                push ecx
                call handle_FloorCursorPos
                add esp, 8

            pop ecx
            test al, al
            jnz cont

            xor eax, eax
            retn 4

cont:
            push ebx
            push ebp
            push esi
            mov esi, dword ptr [esp+0x10]
            jmp Address::Inst.CTrackManiaEditorTerrain__FloorCursorPos_retnpos
        }
    }

    bool BlockMixHooks::handle_FloorCursorPos ( CTrackManiaEditor* pEditor, Vec3Di* pPos )
    {
        return false;
    }

    _declspec(naked) void BlockMixHooks::hook_CreateTerrainBlockAtPos ()
    {
        _asm
        {
            mov [edi+8], edx

            lea eax, [edi+4]
            push eax
            push esi
            call handle_CreateTerrainBlockAtPos
            add esp, 8

            mov ecx, [edi+4]
            jmp Address::Inst.CTrackManiaEditorTerrain__CreateTerrainBlockAtPos_retnpos
        }
    }

    void BlockMixHooks::handle_CreateTerrainBlockAtPos ( CTrackManiaEditor* pEditor, Vec3Di* pPos )
    {
        pPos->Y = pEditor->GetCursor ()->GetPosition ().Y;
    }

} }
