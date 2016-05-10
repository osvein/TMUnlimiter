#pragma once

class Address
{
public:
						Address					();

	static Address		Inst;

	byte*				CodeBase;
	uint				CodeSize;

    byte*               operator_new;
    byte*               operator_delete;

    byte*               CGameCtnArticle__ParsePagePath_hookpos;
    byte*               CGameCtnArticle__ParsePagePath_retnpos;

    byte*               CGameCtnBlock__ReadWrite_hookpos;
    byte*               CGameCtnBlock__ReadWrite_retnpos;

    byte*				CGameCtnBlockInfo__GetNumBlockUnitInfos;
    byte*				CGameCtnBlockInfo__GetBlockUnitInfo;

	byte*				CGameCtnChallenge__RemoveBlock_hookpos;

	byte*				CGameCtnChallenge__IsBlockOnGround_hookpos;
	byte*				CGameCtnChallenge__IsBlockOnGround_retnpos;

    byte*               CGameCtnCatalog__Instance;

	byte*				CGameCtnChallenge__CreateBlockClip_hookpos;
	byte*				CGameCtnChallenge__CreateBlockClip_retnpos;

	byte*				CGameCtnChallenge__InitBuildArea_hookpos;
	byte*				CGameCtnChallenge__InitBuildArea_retnpos;

	byte*				CGameCtnChallenge__GetZoneAtPos_hookpos;

    byte*               CGameCtnChallenge__LoadCollectionAndDecoration_hookpos;

	byte*				CGameCtnChallenge__UpdateFieldUnitsForBlock_hookpos;
	byte*				CGameCtnChallenge__UpdateFieldUnitsForBlock_retnpos;

    byte*               CGameCtnChallenge__UpdatePylonsAtPos_hookpos;
    byte*               CGameCtnChallenge__UpdatePylonsAtPos_retnpos;

    byte*               CGameCtnCollection__GetArticleByMeta_hookpos;
    byte*               CGameCtnCollection__GetArticleByMeta_retnpos;

    byte*               CGameCtnCollection__GetCollectorByMeta_hookpos;
    byte*               CGameCtnCollection__GetCollectorByMeta_retnpos;

	byte*				CGameCtnCollection__GetZoneByBlockInfo;

    byte*               CMwNod__Release;

    byte*               PushSystemFidParameters;
    byte*               CSystemFidParameters__PtrList;
    byte*               CSystemFidParameters__List;

    byte*               CSystemFidParameters__ctor;

    byte*               CSystemFidParameters__AddSParam;

    byte*               CTrackMania__SetEditor_hookpos;
    byte*               CTrackMania__SetEditor_retnpos;

	byte*				CTrackManiaEditor__ValidateBlockPositionAndPillars;

	byte*				CTrackManiaEditor__PlaceBlock_hookpos;
	byte*				CTrackManiaEditor__PlaceBlock_retnpos;

	byte*				CTrackManiaEditor__ClearAreaForBlock_hookpos;
	byte*				CTrackManiaEditor__ClearAreaForBlock_contpos;
	byte*				CTrackManiaEditor__ClearAreaForBlock_skippos;

	byte*				CTrackManiaEditor__RemoveBlock_hookpos;
	byte*				CTrackManiaEditor__RemoveBlock_contpos;
	byte*				CTrackManiaEditor__RemoveBlock_skippos;

	byte*				CTrackManiaEditor__RemoveBlockSafe_hookpos;
	byte*				CTrackManiaEditor__RemoveBlockSafe_contpos;
	byte*				CTrackManiaEditor__RemoveBlockSafe_skippos;

	byte*				CTrackManiaEditor__ConnectDirFromRoadBlock_hookpos;

	byte*				CTrackManiaEditor__CreateRoadBlock_hookpos;
	byte*				CTrackManiaEditor__CreateRoadBlock_retnpos;

	byte*				CTrackManiaEditor__ProcessKey_hookpos1;
	byte*				CTrackManiaEditor__ProcessKey_hookpos2;
	byte*				CTrackManiaEditor__ProcessKey_hookpos3;
    byte*               CTrackManiaEditor__ProcessKey_SwitchToTerrainEditor_hookpos;
    byte*               CTrackManiaEditor__ProcessKey_SwitchToTerrainEditor_retnpos;

	byte*				CTrackManiaEditor__MoveCursorDown_hookpos;

    byte*               CTrackManiaEditorIcon__ctor;

    byte*               CTrackManiaEditorIcon__SetArticle;

    byte*               CTrackManiaEditorIconPage__ctor;

    byte*               CTrackManiaEditorInterface__ctor;

    byte*               CTrackManiaEditorInterface__Cleanup_hookpos;
    byte*               CTrackManiaEditorInterface__Cleanup_retnpos;

    byte*               CTrackManiaEditorInterface__CreateArticleIcons;

    byte*               CTrackManiaEditorInterface__InitGUI_hookpos;
    byte*               CTrackManiaEditorInterface__InitGUI_retnpos;

	byte*				CTrackManiaEditorTerrain__FloorCursorPos_hookpos;
	byte*				CTrackManiaEditorTerrain__FloorCursorPos_retnpos;

	byte*				CTrackManiaEditorTerrain__CreateTerrainBlockAtPos_hookpos;
	byte*				CTrackManiaEditorTerrain__CreateTerrainBlockAtPos_retnpos;

    byte*               SParam_Id__ctor;

    byte*               StringA__Reserve;
    byte*               StringA__pszEmpty;

    byte*               StringKey__Assign;

	byte*				StringKey__Resolve;

    byte*               CreateNodFromFid;

private:
	byte*				FindOffsettedPattern	( byte* pPattern, uint uiPatternSize, int iOffset );
    byte*				FindOffsettedPattern	( byte* pPattern, byte* pMask, uint uiPatternSize, int iOffset );

    PatternFinder       m_PatternFinder;
};
