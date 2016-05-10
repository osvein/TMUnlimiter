#include "StdInc.h"

using namespace TrackMania;

namespace Hooks { namespace Editor {

    float EnvironmentMixHooks::ms_fPylonHeightRatio = 1.0f;
    bool EnvironmentMixHooks::ms_bInEditor;
    std::vector < int > EnvironmentMixHooks::ms_SelectedIconPathBackup;

    void EnvironmentMixHooks::Init ()
    {
        static HookEntry hooks[] = {
            // Make sure all environments have a pylon block info (so that e.g. Alpine
            // roads placed in a Stadium track still have their pylons)
            { Address::Inst.CGameCtnChallenge__LoadCollectionAndDecoration_hookpos, &hook_LoadCollectionAndDecoration },

            // Add an additional categorization level to loaded articles (blocks), to group them
            // by environment
            { Address::Inst.CGameCtnArticle__ParsePagePath_hookpos, &hook_CGameCtnArticle__ParsePagePath },

            // Load and save blocks with their actual environment instead of the track's
            { Address::Inst.CGameCtnBlock__ReadWrite_hookpos, &hook_ReadWriteBlock },

            // Retrieve block information from the block's actual environment instead of the track's
            { Address::Inst.CGameCtnCollection__GetArticleByMeta_hookpos, &hook_GetArticleByMeta },
            { Address::Inst.CGameCtnCollection__GetCollectorByMeta_hookpos, &hook_GetCollectorByMeta },

            // Store the path to the selected editor icon when the editor interface is about to be
            // re-created
            { Address::Inst.CTrackManiaEditorInterface__Cleanup_hookpos, &hook_CleanupEditorInterface },

            // Catch editor switches
            { Address::Inst.CTrackMania__SetEditor_hookpos, &hook_SetEditor },

            // Create menu items for all environments, not just the selected one
            // Restore the selected icon path
            { Address::Inst.CTrackManiaEditorInterface__InitGUI_hookpos, &hook_InitEditorGUI },

            // Change the logic of when to switch to terrain editing mode. Normally this is
            // done when clicking the leftmost root icon; now, this is no longer valid
            // (the leftmost root icon is now the Alpine environment, not the terrain block
            // category). Instead, check for the "Terraformation" icon page name.
            { Address::Inst.CTrackManiaEditor__ProcessKey_SwitchToTerrainEditor_hookpos, &hook_ShouldSwitchToTerrainEditor },

            // Look up block zones in the block's collection (environment) instead of the
            // challenge's collection.
            { Address::Inst.CGameCtnCollection__GetZoneByBlockInfo, &hook_GetZoneByBlockInfo },

            // Scale pylon heights to account for square height differences between environments
            { Address::Inst.CGameCtnChallenge__UpdatePylonsAtPos_hookpos, &hook_SetUpPylon },

            { NULL, NULL }
        };
        InstallHooks ( hooks );
    }

    _declspec(naked) void EnvironmentMixHooks::hook_LoadCollectionAndDecoration ()
    {
        _asm
        {
            push ebx
            call handle_LoadCollectionAndDecoration
            add esp, 4

            pop edi
            pop esi
            pop ebp
            pop ebx
            add esp, 0x6C
            retn 4
        }
    }

    void EnvironmentMixHooks::handle_LoadCollectionAndDecoration ( CGameCtnChallenge* pChallenge )
    {
        // Load all collections, find the Desert (Speed) pylon block info as a default for pylonless environments
        std::vector < CGameCtnCollection* > collections;
        CGameCtnCatalog* pCatalog = CGameCtnCatalog::GetInstance ();
        CGameCtnBlockInfo* pDefaultPylonBlockInfo = NULL;
        for ( auto it = pCatalog->GetChapters ().Begin (); it != pCatalog->GetChapters ().End (); it++ )
        {
            CGameCtnCollection* pCollection = (*it)->LoadCollection ();
            if ( !pCollection )
                continue;

            if ( !strcmp ( pCollection->GetEnvironmentName (), "Speed" ) )
            {
                CGameCtnZone* pZone = pCollection->GetDefaultZone ();
                if ( pZone && pZone->GetType () == CGameCtnZone::FLAT )
                    pDefaultPylonBlockInfo = ((CGameCtnZoneFlat *)pZone)->GetPylonBlockInfo ();
            }

            collections.push_back ( pCollection );
        }

        if ( !pDefaultPylonBlockInfo )
            return;

        // Assign the pylon block info to any collections that don't have one
        for ( auto it = collections.begin (); it != collections.end (); it++ )
        {
            CGameCtnZone* pZone = (*it)->GetDefaultZone ();
            if ( pZone && pZone->GetType () == CGameCtnZone::FLAT )
            {
                if ( !((CGameCtnZoneFlat *)pZone)->GetPylonBlockInfo () )
                    ((CGameCtnZoneFlat *)pZone)->SetPylonBlockInfo ( pDefaultPylonBlockInfo );
            }
        }

        // Calculate the pylon block height ratio
        ms_fPylonHeightRatio = 1.0f;
        CGameCtnCollection* pChallengeCollection = pChallenge->GetCollection ();
        CGameCtnZone* pChallengeZone = pChallengeCollection->GetDefaultZone ();
        if ( pChallengeZone && pChallengeZone->GetType () == CGameCtnZone::FLAT )
        {
            CGameCtnBlockInfo* pChallengePylonBlockInfo = ((CGameCtnZoneFlat *)pChallengeZone)->GetPylonBlockInfo ();
            CGameCtnCollection* pPylonCollection = pCatalog->GetChapterByMeta (
                pChallengePylonBlockInfo->GetBlockMeta () )->GetCollection ();
            ms_fPylonHeightRatio = (float)pChallengeCollection->GetSquareHeight () / (float)pPylonCollection->GetSquareHeight ();
        }
    }

    _declspec(naked) void EnvironmentMixHooks::hook_CGameCtnArticle__ParsePagePath ()
    {
        _asm
        {
            mov eax, esi
            sub eax, 0x6C
            push eax
            call handle_CGameCtnArticle__ParsePagePath
            add esp, 4

            lea eax, [esp+0x28]
            push eax
            jmp Address::Inst.CGameCtnArticle__ParsePagePath_retnpos
        }
    }

    void EnvironmentMixHooks::handle_CGameCtnArticle__ParsePagePath ( CGameCtnArticle* pArticle )
    {
        const char* pszEnvironment = pArticle->GetArticleMeta ()->m_skEnvironment.Resolve ();
        if ( !pszEnvironment )
            return;

        pArticle->GetPagePathParts ().Add ( pszEnvironment );
    }

    _declspec(naked) void EnvironmentMixHooks::hook_ReadWriteBlock ()
    {
        _asm
        {
            mov eax, [esp+0x14]
            push [eax]
            push esi
            call handle_ReadWriteBlock
            add esp, 8

            mov ecx, eax
            jmp Address::Inst.CGameCtnBlock__ReadWrite_retnpos
        }
    }

    dword EnvironmentMixHooks::handle_ReadWriteBlock ( CGameCtnBlock* pBlock, StringKey skChallengeEnvironment )
    {
        CGameCtnCatalog* pCatalog = CGameCtnCatalog::GetInstance ();

        NodeMeta meta = *pBlock->GetBlockMeta ();
        if ( meta.m_skEnvironment.GetKey () == -1 )
            meta.m_skEnvironment = skChallengeEnvironment;
        if ( pCatalog->GetArticleByMeta ( &meta ) )
            return meta.m_skEnvironment.GetKey ();

        for ( auto it = pCatalog->GetChapters ().Begin (); it != pCatalog->GetChapters ().End (); it++ )
        {
            meta.m_skEnvironment.SetKey ( (*it)->GetNameKey () );
            if ( (*it)->GetArticleByMeta ( &meta ) )
                return meta.m_skEnvironment.GetKey ();
        }
        return skChallengeEnvironment.GetKey ();
    }

    _declspec(naked) void EnvironmentMixHooks::hook_GetArticleByMeta ()
    {
        _asm
        {
            push eax
            push ebx
            push ebp
            push esi
            push edi

            lea eax, [esp+0x1C+4]
            push eax
            push ecx
            call handle_GetCollectorByMeta
            add esp, 8

            mov ecx, eax
            jmp Address::Inst.CGameCtnCollection__GetArticleByMeta_retnpos
        }
    }

    _declspec(naked) void EnvironmentMixHooks::hook_GetCollectorByMeta ()
    {
        _asm
        {
            push [esp+4]
            push ecx
            call handle_GetCollectorByMeta
            add esp, 8

            mov ecx, eax
            push ebx
            push ebp
            push esi
            push edi
            lea edi, [ecx+0x50]
            jmp Address::Inst.CGameCtnCollection__GetCollectorByMeta_retnpos
        }
    }

    CGameCtnCollection* EnvironmentMixHooks::handle_GetCollectorByMeta ( CGameCtnCollection* pCollection, NodeMeta* pMeta )
    {
        if ( pCollection->GetEnvironmentNameKey () == pMeta->m_skEnvironment.GetKey () )
            return pCollection;

        CGameCtnChapter* pChapter = CGameCtnCatalog::GetInstance ()->GetChapterByMeta ( pMeta );
        if ( !pChapter )
            return pCollection;

        return pChapter->LoadCollection ();
    }

    _declspec(naked) void EnvironmentMixHooks::hook_ShouldSwitchToTerrainEditor ()
    {
        _asm
        {
            push ebp
            call handle_ShouldSwitchToTerrainEditor
            add esp, 4

            cmp al, 1
            mov eax, -1
            mov ecx, 4
            jmp Address::Inst.CTrackManiaEditor__ProcessKey_SwitchToTerrainEditor_retnpos
        }
    }

    bool EnvironmentMixHooks::handle_ShouldSwitchToTerrainEditor ( CTrackManiaEditor* pEditor )
    {
        CTrackManiaEditorIconPage* pSelectedIconPage = pEditor->GetEditorInterface ()->GetSelectedIconPage ();
        if ( !pSelectedIconPage || pSelectedIconPage->GetIcons ().Size () == 0 )
            return false;

        CTrackManiaEditorIcon* pClickedIcon = pSelectedIconPage->GetIcons () [ 0 ];
        CTrackManiaEditorIconPage* pTargetIconPage = pClickedIcon->GetIconPage ();
        if ( !pTargetIconPage )
            return false;

        bool bResult = strcmp ( pTargetIconPage->GetName (), "Terraformation" ) == 0;
        if ( bResult )
        {
            std::vector < int > iconPagePath = pEditor->GetEditorInterface ()->GetSelectedIconPath ();
            iconPagePath.push_back ( 0 );
            pEditor->GetEditorInterface ()->SetSelectedIconPath ( iconPagePath );
        }

        return bResult;
    }

    _declspec(naked) void EnvironmentMixHooks::hook_CleanupEditorInterface ()
    {
        _asm
        {
            push ecx
                push ecx
                call handle_CleanupEditorInterface
                add esp, 4
            pop ecx

            push ebx
            push esi
            mov esi, ecx
            lea ecx, [esi+0x3C]
            jmp Address::Inst.CTrackManiaEditorInterface__Cleanup_retnpos
        }
    }

    void EnvironmentMixHooks::handle_CleanupEditorInterface ( CTrackManiaEditorInterface* pInterface )
    {
        if ( ms_bInEditor && ms_SelectedIconPathBackup.empty () )
            ms_SelectedIconPathBackup = pInterface->GetSelectedIconPath ();
    }

    _declspec(naked) void EnvironmentMixHooks::hook_SetEditor ()
    {
        _asm
        {
            push ecx
                push [esp+4+4]
                push [ecx+0x414]
                call handle_SetEditor
                add esp, 8
            pop ecx

            push esi
            push edi
            mov edi, [esp+8+4]
            jmp Address::Inst.CTrackMania__SetEditor_retnpos
        }
    }

    void EnvironmentMixHooks::handle_SetEditor ( CTrackManiaEditor* pOldEditor, CTrackManiaEditor* pNewEditor )
    {
        if ( !pNewEditor )
        {
            // Leaving the editor: clear state
            ms_SelectedIconPathBackup.clear ();
        }
        ms_bInEditor = ( pNewEditor != NULL );
    }

    _declspec(naked) void EnvironmentMixHooks::hook_InitEditorGUI ()
    {
        _asm
        {
            push ecx
            call handle_InitEditorGUI
            add esp, 0x14

            jmp Address::Inst.CTrackManiaEditorInterface__InitGUI_retnpos
        }
    }

    void EnvironmentMixHooks::handle_InitEditorGUI ( CTrackManiaEditorInterface* pEditorInterface, void* pGameInterface, CGameCtnCollection* pCollection, CGameCtnDecoration* pDecoration, CGameCtnCollectorList* pCollectorList )
    {
        CGameCtnCatalog* pCatalog = CGameCtnCatalog::GetInstance ();
        for ( int i = 0; i < pCatalog->GetChapters ().Size (); i++ )
        {
            CGameCtnChapter* pChapter = pCatalog->GetChapters () [ i ];
            if ( !pChapter->GetCollectionFid () )
                continue;

            pCollection = pChapter->LoadCollection ();
            if ( !pCollection )
                continue;

            pCollection->AddRef ();
            pEditorInterface->CreateArticleIcons ( pGameInterface, pCollection, pDecoration, pCollectorList );
        }

        // Temporary hack: remove terrain categories of environments other than the
        // track's one, as selecting these crashes the game...
        const char* pszEnvName = pEditorInterface->GetEditor ()->GetChallenge ()->GetCollection ()->GetEnvironmentName ();
        List < CTrackManiaEditorIconPage* >& rootIconPages = pEditorInterface->GetRootIconPages ();
        for ( auto it = rootIconPages.Begin (); it != rootIconPages.End (); it++ )
        {
            if ( !strcmp ( (*it)->GetName (), pszEnvName ) )
                continue;

            CTrackManiaEditorIconPage* pTerraformationPage = (*it)->GetIconPageByName ( "Terraformation" );
            if ( pTerraformationPage )
                (*it)->RemoveIcon ( pTerraformationPage->GetParentIcon () );
        }

        // Restore the selected icon
        if ( !ms_SelectedIconPathBackup.empty () )
        {
            pEditorInterface->SetSelectedIconPath ( ms_SelectedIconPathBackup );
            ms_SelectedIconPathBackup.clear ();
        }
    }

    _declspec(naked) void EnvironmentMixHooks::hook_GetZoneByBlockInfo ()
    {
        _asm
        {
            push [esp+4]
            call CGameCtnCollection::GetZoneByBlockInfo
            add esp, 4

            retn 4
        }
    }

    _declspec(naked) void EnvironmentMixHooks::hook_SetUpPylon ()
    {
        _asm
        {
            push ecx
            call handle_SetUpPylon
            add esp, 0xC

            jmp Address::Inst.CGameCtnChallenge__UpdatePylonsAtPos_retnpos
        }
    }

    void EnvironmentMixHooks::handle_SetUpPylon ( CGameCtnPylonColumn* pPylon, int iBottomY, int iTopY )
    {
        if ( iBottomY < 0 || iTopY < 0 )
        {
            pPylon->SetBottomY ( iBottomY );
            pPylon->SetTopY ( iTopY );
            return;
        }

        int iHeight = static_cast < int > ( (iTopY - iBottomY)*ms_fPylonHeightRatio );
        pPylon->SetBottomY ( iBottomY );
        pPylon->SetTopY ( iBottomY + iHeight );
    }

} }
