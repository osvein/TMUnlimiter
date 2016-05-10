#include "StdInc.h"

Address Address::Inst;

Address::Address ()
{
	CodeBase = (byte *)0x401000;
	CodeSize = 0x727000;

	m_PatternFinder.Init ( CodeBase, CodeSize );

    static byte patOperatorNew[] = {
	    0x74, 0xE6, 0xC9, 0xC3, 0xF6, 0x05
    };
    operator_new = FindOffsettedPattern ( patOperatorNew, sizeof(patOperatorNew), 0x20 );

    static byte patOperatorDelete[] = {
	    0x83, 0x7D, 0xE4, 0x00, 0x75, 0x37, 0xFF, 0x75, 0x08
    };
    operator_delete = FindOffsettedPattern ( patOperatorDelete, sizeof(patOperatorDelete), 0x4B );

    static byte patParseArticlePagePath[] = {
	    0x8D, 0x71, 0x6C, 0x6A, 0x00, 0x8B, 0xCE
    };
    byte* CGameCtnArticle__ParsePagePath = FindOffsettedPattern ( patParseArticlePagePath, sizeof(patParseArticlePagePath), 0x24 );
    CGameCtnArticle__ParsePagePath_hookpos = CGameCtnArticle__ParsePagePath + 0x38;
    CGameCtnArticle__ParsePagePath_retnpos = CGameCtnArticle__ParsePagePath + 0x3D;

    static byte patReadWriteBlock[] = {
	    0x8D, 0x56, 0x54, 0x89, 0x4E, 0x18
    };
    byte* CGameCtnBlock__ReadWrite = FindOffsettedPattern ( patReadWriteBlock, sizeof(patReadWriteBlock), 0x2E );
    CGameCtnBlock__ReadWrite_hookpos = CGameCtnBlock__ReadWrite + 0x25;
    CGameCtnBlock__ReadWrite_retnpos = CGameCtnBlock__ReadWrite + 0x2B;

    static byte patGetNumBlockUnits[] = {
        0x83, 0x7C, 0x24, 0x04, 0x00, 0x74, 0x0E, 0x81, 0xC1, 0xEC, 0x00, 0x00, 0x00
    };
    CGameCtnBlockInfo__GetNumBlockUnitInfos = FindOffsettedPattern ( patGetNumBlockUnits,
        sizeof(patGetNumBlockUnits), 0 );

    static byte patGetBlockUnitInfo[] = {
        0x83, 0x7C, 0x24, 0x08, 0x00, 0x74, 0x15, 0x8B, 0x44, 0x24, 0x04
    };
    CGameCtnBlockInfo__GetBlockUnitInfo = FindOffsettedPattern ( patGetBlockUnitInfo,
        sizeof(patGetBlockUnitInfo), 0 );

	static byte patChallengeRemoveBlock[] = {
		0x39, 0x5D, 0x24, 0x74, 0xF4
	};
	byte* CGameCtnChallenge__RemoveBlock = FindOffsettedPattern ( patChallengeRemoveBlock,
		sizeof(patChallengeRemoveBlock), 0x3A );
	CGameCtnChallenge__RemoveBlock_hookpos = CGameCtnChallenge__RemoveBlock + 0x268;

	static byte patIsBlockOnGround[] = {
		0x83, 0x78, 0x1C, 0x00, 0x75, 0x34
	};
	byte* CGameCtnChallenge__IsBlockOnGround = FindOffsettedPattern ( patIsBlockOnGround,
		sizeof(patIsBlockOnGround), 0x5A );
	CGameCtnChallenge__IsBlockOnGround_hookpos = CGameCtnChallenge__IsBlockOnGround;
	CGameCtnChallenge__IsBlockOnGround_retnpos = CGameCtnChallenge__IsBlockOnGround + 0x8;

	static byte patCreateBlockClip[] = {
		0x8B, 0x40, 0x34, 0x85, 0xC0, 0x89, 0x44, 0x24, 0x14, 0x75, 0x10
	};
	byte* CGameCtnChallenge__CreateBlockClip = FindOffsettedPattern ( patCreateBlockClip,
		sizeof(patCreateBlockClip), 0xDA );
	CGameCtnChallenge__CreateBlockClip_hookpos = CGameCtnChallenge__CreateBlockClip + 0x7;
	CGameCtnChallenge__CreateBlockClip_retnpos = CGameCtnChallenge__CreateBlockClip + 0xD;

	static byte patInitBuildArea[] = {
		0x89, 0x86, 0xB0, 0x00, 0x00, 0x00, 0x8B, 0x86, 0x90, 0x00, 0x00, 0x00, 0xD9, 0x40, 0x7C
	};
	byte* CGameCtnChallenge__InitBuildArea = FindOffsettedPattern ( patInitBuildArea,
		sizeof(patInitBuildArea), 0x51 );
	CGameCtnChallenge__InitBuildArea_hookpos = CGameCtnChallenge__InitBuildArea + 0x3C;
	CGameCtnChallenge__InitBuildArea_retnpos = CGameCtnChallenge__InitBuildArea + 0x57;

	static byte patGetZoneAtPos[] = {
		0x8B, 0x7C, 0x24, 0x14, 0x8B, 0xF1, 0x8B, 0x4C, 0x24, 0x0C
	};
	byte* CGameCtnChallenge__GetZoneAtPos = FindOffsettedPattern ( patGetZoneAtPos,
		sizeof(patGetZoneAtPos), 0x2 );
	CGameCtnChallenge__GetZoneAtPos_hookpos = CGameCtnChallenge__GetZoneAtPos + 0x31;

    static byte patLoadCollectionAndDecoration[] = {
        0x8B, 0x48, 0x58, 0x8B, 0x51, 0x38, 0x89, 0x93, 0x44, 0x01, 0x00, 0x00
    };
    byte* CGameCtnChallenge__LoadCollectionAndDecoration = FindOffsettedPattern ( patLoadCollectionAndDecoration,
        sizeof(patLoadCollectionAndDecoration), 0x25E );
    CGameCtnChallenge__LoadCollectionAndDecoration_hookpos = CGameCtnChallenge__LoadCollectionAndDecoration + 0x276;

	static byte patUpdateFieldUnitsForBlock[] = {
		0x89, 0x6C, 0x24, 0x2C, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x0C, 0x07, 0x00, 0x00
	};
	byte* CGameCtnChallenge__UpdateFieldUnitsForBlock = FindOffsettedPattern ( patUpdateFieldUnitsForBlock,
		sizeof(patUpdateFieldUnitsForBlock), 0x37 );
	CGameCtnChallenge__UpdateFieldUnitsForBlock_hookpos = CGameCtnChallenge__UpdateFieldUnitsForBlock + 0x3F;
	CGameCtnChallenge__UpdateFieldUnitsForBlock_retnpos = CGameCtnChallenge__UpdateFieldUnitsForBlock + 0x74B;

    static byte patUpdatePylonsAtPos[] = {
        0x3C, 0x01, 0x74, 0x3C, 0x3C, 0x02, 0x74, 0x2A, 0x3C, 0x03, 0x74, 0x26
    };
    byte* CGameCtnChallenge__UpdatePylonsAtPos = FindOffsettedPattern ( patUpdatePylonsAtPos,
        sizeof(patUpdatePylonsAtPos), 0x1D0 );
    CGameCtnChallenge__UpdatePylonsAtPos_hookpos = CGameCtnChallenge__UpdatePylonsAtPos + 0x3C5;
    CGameCtnChallenge__UpdatePylonsAtPos_retnpos = CGameCtnChallenge__UpdatePylonsAtPos_hookpos + 5;

    static byte patGetArticleByMeta[] = {
	    0x85, 0xDB, 0x76, 0x29, 0x8B, 0x6C, 0x24, 0x24
    };
    byte* CGameCtnCollection__GetArticleByMeta = FindOffsettedPattern ( patGetArticleByMeta, sizeof(patGetArticleByMeta), 0x32 );
    CGameCtnCollection__GetArticleByMeta_hookpos = CGameCtnCollection__GetArticleByMeta + 0xD;
    CGameCtnCollection__GetArticleByMeta_retnpos = CGameCtnCollection__GetArticleByMeta + 0x12;

    static byte patGetCollectorByMeta[] = {
	    0x83, 0xC0, 0x18, 0x39, 0x18, 0x75, 0x0C
    };
    byte* CGameCtnCollection__GetCollectorByMeta = FindOffsettedPattern ( patGetCollectorByMeta, sizeof(patGetCollectorByMeta), 0x2A );
    CGameCtnCollection__GetCollectorByMeta_hookpos = CGameCtnCollection__GetCollectorByMeta;
    CGameCtnCollection__GetCollectorByMeta_retnpos = CGameCtnCollection__GetCollectorByMeta + 0x7;

	static byte patGetZoneByBlockInfo[] = {
		0x83, 0xC6, 0x01, 0x3B, 0xF3, 0x72, 0xD1, 0x8D, 0x7D, 0x2C
	};
	CGameCtnCollection__GetZoneByBlockInfo = FindOffsettedPattern ( patGetZoneByBlockInfo,
		sizeof(patGetZoneByBlockInfo), 0x40 );

    static byte patReleaseNod[] = {
	    0x3B, 0xEF, 0x72, 0xD0, 0x8B, 0x44, 0x24, 0x10
    };
    CMwNod__Release = FindOffsettedPattern ( patReleaseNod, sizeof(patReleaseNod), 0x5F );

    static byte patPushFidParameters[] = {
        0x85, 0xDB, 0x0F, 0x86, 0x7F, 0x00, 0x00, 0x00, 0x83, 0xC5, 0x04
    };
    PushSystemFidParameters = FindOffsettedPattern ( patPushFidParameters, sizeof(patPushFidParameters), 0x62 );
    CSystemFidParameters__PtrList = (byte *)( *(dword *)(PushSystemFidParameters + 0xA) );
    CSystemFidParameters__List = (byte *)( *(dword *)(PushSystemFidParameters + 0x14) );

    static byte patSystemFidParametersCtor[] = {
        0x8B, 0xCF, 0x89, 0x44, 0x24, 0x1C, 0x89, 0x46, 0x28, 0x89, 0x46, 0x2C
    };
    CSystemFidParameters__ctor = FindOffsettedPattern ( patSystemFidParametersCtor, sizeof(patSystemFidParametersCtor), 0x3D );

    static byte patAddSParam[] = {
        0x3B, 0xC3, 0x89, 0x44, 0x24, 0x14, 0x76, 0x44
    };
    CSystemFidParameters__AddSParam = FindOffsettedPattern ( patAddSParam, sizeof(patAddSParam), 0x29 );

    static byte patSetTrackManiaEditor[] = {
        0x3B, 0xBE, 0x14, 0x04, 0x00, 0x00, 0x74, 0x20
    };
    byte* CTrackMania__SetEditor = FindOffsettedPattern ( patSetTrackManiaEditor, sizeof(patSetTrackManiaEditor), 0x8 );
    CTrackMania__SetEditor_hookpos = CTrackMania__SetEditor;
    CTrackMania__SetEditor_retnpos = CTrackMania__SetEditor + 0x6;

	static byte patValidateBlockPositionAndPillars[] = {
		0x39, 0x96, 0xCC, 0x04, 0x00, 0x00, 0x0F, 0x84, 0xC9, 0x00, 0x00, 0x00
	};
	CTrackManiaEditor__ValidateBlockPositionAndPillars = FindOffsettedPattern (
		patValidateBlockPositionAndPillars, sizeof(patValidateBlockPositionAndPillars), 0xE );

	static byte patPlaceBlock[] = {
		0x83, 0x79, 0x7C, 0x05, 0x8B, 0xE8, 0x89, 0x6C, 0x24, 0x48, 0x75, 0x27
	};
	byte* CTrackManiaEditor__PlaceBlock = FindOffsettedPattern ( patPlaceBlock, sizeof(patPlaceBlock), 0x4B );
	CTrackManiaEditor__PlaceBlock_hookpos = CTrackManiaEditor__PlaceBlock + 0x19D;
	CTrackManiaEditor__PlaceBlock_retnpos = CTrackManiaEditor__PlaceBlock + 0x316;

	static byte patClearAreaForBlock[] = {
		0x83, 0xB9, 0xE4, 0x00, 0x00, 0x00, 0x00, 0x75, 0x3A
	};
	byte* CTrackManiaEditor__ClearAreaForBlock = FindOffsettedPattern ( patClearAreaForBlock,
		sizeof(patClearAreaForBlock), 0xB4 );
	CTrackManiaEditor__ClearAreaForBlock_hookpos = CTrackManiaEditor__ClearAreaForBlock + 0xA7;
	CTrackManiaEditor__ClearAreaForBlock_contpos = CTrackManiaEditor__ClearAreaForBlock + 0xAE;
	CTrackManiaEditor__ClearAreaForBlock_skippos = CTrackManiaEditor__ClearAreaForBlock + 0x109;

	static byte patRemoveBlock[] = {
		0x83, 0xB9, 0x0C, 0x01, 0x00, 0x00, 0x00, 0x74, 0x21
	};
	byte* CTrackManiaEditor__RemoveBlock = FindOffsettedPattern ( patRemoveBlock, sizeof(patRemoveBlock), 0xF5 );
	CTrackManiaEditor__RemoveBlock_hookpos = CTrackManiaEditor__RemoveBlock + 0x82;
	CTrackManiaEditor__RemoveBlock_contpos = CTrackManiaEditor__RemoveBlock + 0x87;
	CTrackManiaEditor__RemoveBlock_skippos = CTrackManiaEditor__RemoveBlock + 0xEA;

	static byte patRemoveBlockSafe[] = {
		0x8B, 0x43, 0x60, 0xA9, 0x00, 0x40, 0x00, 0x00, 0x74, 0x1F
	};
	byte* CTrackManiaEditor__RemoveBlockSafe = FindOffsettedPattern ( patRemoveBlockSafe,
		sizeof(patRemoveBlockSafe), 0x8A );
	CTrackManiaEditor__RemoveBlockSafe_hookpos = CTrackManiaEditor__RemoveBlockSafe + 0x423;
	CTrackManiaEditor__RemoveBlockSafe_contpos = CTrackManiaEditor__RemoveBlockSafe + 0x42D;
	CTrackManiaEditor__RemoveBlockSafe_skippos = CTrackManiaEditor__RemoveBlockSafe + 0x496;

	static byte patConnectDirFromRoadBlock[] = {
		0x8B, 0x58, 0x04, 0x85, 0xDB, 0x0F, 0x84, 0x48, 0x01, 0x00, 0x00
	};
	byte* CTrackManiaEditor__ConnectDirFromRoadBlock = FindOffsettedPattern ( patConnectDirFromRoadBlock,
		sizeof(patConnectDirFromRoadBlock), 0x84 );
	CTrackManiaEditor__ConnectDirFromRoadBlock_hookpos = CTrackManiaEditor__ConnectDirFromRoadBlock + 0x1B0;

	static byte patCreateRoadBlock[] = {
		0x8B, 0x4E, 0x20, 0x8B, 0x89, 0x94, 0x00, 0x00, 0x00, 0x89, 0x44, 0x24, 0x1C
	};
	byte* CTrackManiaEditor__CreateRoadBlock = FindOffsettedPattern ( patCreateRoadBlock,
		sizeof(patCreateRoadBlock), 0x100 );
	CTrackManiaEditor__CreateRoadBlock_hookpos = CTrackManiaEditor__CreateRoadBlock + 0x138;
	CTrackManiaEditor__CreateRoadBlock_retnpos = CTrackManiaEditor__CreateRoadBlock + 0x13D;

	static byte patProcessKey[] = {
		0x85, 0xC0, 0x0F, 0x85, 0x1D, 0x04, 0x00, 0x00, 0x39, 0xB5, 0x7C, 0x04,
		0x00, 0x00, 0x74, 0x0D
	};
	byte* CTrackManiaEditor__ProcessKey = FindOffsettedPattern ( patProcessKey,
		sizeof(patProcessKey), 0xB8 );
	CTrackManiaEditor__ProcessKey_hookpos1 = CTrackManiaEditor__ProcessKey + 0x1297;
	CTrackManiaEditor__ProcessKey_hookpos2 = CTrackManiaEditor__ProcessKey + 0x12D3;
	CTrackManiaEditor__ProcessKey_hookpos3 = CTrackManiaEditor__ProcessKey + 0x212A;
    CTrackManiaEditor__ProcessKey_SwitchToTerrainEditor_hookpos = CTrackManiaEditor__ProcessKey + 0x1BE9;
    CTrackManiaEditor__ProcessKey_SwitchToTerrainEditor_retnpos = CTrackManiaEditor__ProcessKey + 0x1BF2;

	static byte patMoveCursorDown[] = {
		0x0F, 0x86, 0x00, 0x01, 0x00, 0x00, 0x8B, 0x46, 0x48, 0x83, 0xC1, 0xFF
	};
	byte* CTrackManiaEditor__MoveCursorDown = FindOffsettedPattern ( patMoveCursorDown,
		sizeof(patMoveCursorDown), 0x10 );
	CTrackManiaEditor__MoveCursorDown_hookpos = CTrackManiaEditor__MoveCursorDown + 0x90;

    static byte patIconCtor[] = {
	    0x33, 0xC0, 0x89, 0x46, 0x18, 0x89, 0x46, 0x14
    };
    CTrackManiaEditorIcon__ctor = FindOffsettedPattern ( patIconCtor, sizeof(patIconCtor), 0x8 );

    static byte patSetIconArticle[] = {
	    0x89, 0x7E, 0x18, 0xC7, 0x46, 0x14, 0x00, 0x00, 0x00, 0x00, 0x74, 0x35
    };
    CTrackManiaEditorIcon__SetArticle = FindOffsettedPattern ( patSetIconArticle, sizeof(patSetIconArticle), 0x19 );

    static byte patIconPageCtor[] = {
	    0x8D, 0x7E, 0x14, 0x89, 0x1F
    };
    CTrackManiaEditorIconPage__ctor = FindOffsettedPattern ( patIconPageCtor, sizeof(patIconPageCtor), 0x39 );

    static byte patEditorInterfaceCtor[] = {
        0x89, 0x79, 0x08, 0x72, 0x9D
    };
    CTrackManiaEditorInterface__ctor = FindOffsettedPattern ( patEditorInterfaceCtor, sizeof(patEditorInterfaceCtor), 0x111 );

    static byte patCleanupEditorInterface[] = {
        0x8B, 0x46, 0x58, 0x3B, 0xC3, 0x74, 0x73
    };
    byte* CTrackManiaEditorInterface__Cleanup = FindOffsettedPattern ( patCleanupEditorInterface, sizeof(patCleanupEditorInterface), 0x5A );
    CTrackManiaEditorInterface__Cleanup_hookpos = CTrackManiaEditorInterface__Cleanup;
    CTrackManiaEditorInterface__Cleanup_retnpos = CTrackManiaEditorInterface__Cleanup + 0x7;

    static byte patCreateArticleIcons[] = {
        0x8B, 0x40, 0x38, 0x83, 0xC0, 0xFD, 0x83, 0xF8, 0x03
    };
    CTrackManiaEditorInterface__CreateArticleIcons = FindOffsettedPattern ( patCreateArticleIcons, sizeof(patCreateArticleIcons), 0x2C );
    CGameCtnCatalog__Instance = (byte *)(*(dword *)(CTrackManiaEditorInterface__CreateArticleIcons + 0x4C));

    static byte patInitGUI[] = {
        0x89, 0x6F, 0x34, 0x8B, 0x91, 0x24, 0x01, 0x00, 0x00
    };
    byte* CTrackManiaEditorInterface__InitGUI = FindOffsettedPattern ( patInitGUI, sizeof(patInitGUI), 0x4E );
    CTrackManiaEditorInterface__InitGUI_hookpos = CTrackManiaEditorInterface__InitGUI + 0x11C8;
    CTrackManiaEditorInterface__InitGUI_retnpos = CTrackManiaEditorInterface__InitGUI_hookpos + 5;

	static byte patFloorCursor[] = {
		0x39, 0x58, 0x08, 0x74, 0x2B, 0x01, 0x5E, 0x04
	};
	byte* CTrackManiaEditorTerrain__FloorCursorPos = FindOffsettedPattern ( patFloorCursor,
		sizeof(patFloorCursor), 0x35 );
	CTrackManiaEditorTerrain__FloorCursorPos_hookpos = CTrackManiaEditorTerrain__FloorCursorPos;
	CTrackManiaEditorTerrain__FloorCursorPos_retnpos = CTrackManiaEditorTerrain__FloorCursorPos + 0x7;

	static byte patCreateTerrainBlockAtPos[] = {
		0x8B, 0x47, 0x14, 0x6A, 0x00, 0x50, 0x51, 0x89, 0x57, 0x08
	};
	byte* CTrackManiaEditorTerrain__CreateTerrainBlockAtPos = FindOffsettedPattern (
		patCreateTerrainBlockAtPos, sizeof(patCreateTerrainBlockAtPos), 0xC7 );
	CTrackManiaEditorTerrain__CreateTerrainBlockAtPos_hookpos = CTrackManiaEditorTerrain__CreateTerrainBlockAtPos + 0xCE;
	CTrackManiaEditorTerrain__CreateTerrainBlockAtPos_retnpos = CTrackManiaEditorTerrain__CreateTerrainBlockAtPos + 0xD4;

    static byte patSParamIdCtor[] = {
    0x8B, 0x44, 0x24, 0x28, 0x8B, 0x4C, 0x24, 0x24, 0x50, 0x51, 0x6A, 0x02
    };
    SParam_Id__ctor = FindOffsettedPattern ( patSParamIdCtor, sizeof(patSParamIdCtor), 0x28 );

    static byte patStringAReserve[] = {
	    0x74, 0x05, 0x8B, 0x46, 0x04, 0x89, 0x03
    };
    StringA__Reserve = FindOffsettedPattern ( patStringAReserve, sizeof(patStringAReserve), 0xA );
    StringA__pszEmpty = (byte *)( *(dword *)(StringA__Reserve + 0x74) );

    static byte patStringKeyAssign[] = {
        0x74, 0x2F, 0x80, 0x38, 0x00, 0x74, 0x2A
    };
    StringKey__Assign = FindOffsettedPattern ( patStringKeyAssign, sizeof(patStringKeyAssign), 0x9 );

	static byte patStringKeyResolve[] = {
		0x81, 0xF9, 0x00, 0x00, 0x00, 0x80, 0x74, 0x03, 0x33, 0xC0, 0xC3, 0x25, 0xFF, 0xFF, 0xFF, 0x3F
	};
	StringKey__Resolve = FindOffsettedPattern ( patStringKeyResolve, sizeof(patStringKeyResolve), 0x12 );

    static byte patCreateNodFromFid[] = {
	    0x8B, 0x84, 0x24, 0x0C, 0x01, 0x00, 0x00, 0x89, 0x8C, 0x24, 0x80, 0x00, 0x00, 0x00
    };
    CreateNodFromFid = FindOffsettedPattern ( patCreateNodFromFid, sizeof(patCreateNodFromFid), 0x41 );
}

byte* Address::FindOffsettedPattern ( byte* pPattern, uint uiPatternSize, int iOffset )
{
    void* pResult = m_PatternFinder.Find ( pPattern, uiPatternSize );
    if ( !pResult )
	{
		MessageBox ( NULL, "Failed to find the code to patch. Make sure you have TrackMania "
                    "update 2.11.26 installed. Also, the Steam version of the game is NOT supported - "
                    "sorry about that.", "TMUnlimiter", MB_ICONEXCLAMATION );
		ExitProcess ( 0 );
	}
    return (byte *)pResult - iOffset;
}
