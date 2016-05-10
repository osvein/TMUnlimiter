#pragma once

class Address
{
public:
						Address					();

	static Address		Inst;

	byte*				CodeBase;
	uint				CodeSize;

	byte*				CGameCtnChallenge__RemoveBlock_hookpos;

	byte*				CGameCtnChallenge__IsBlockOnGround_hookpos;
	byte*				CGameCtnChallenge__IsBlockOnGround_retnpos;

	byte*				CGameCtnBlockInfo__GetNumBlockUnitInfos;
	byte*				CGameCtnBlockInfo__GetBlockUnitInfo;

	byte*				CGameCtnChallenge__CreateBlockClip_hookpos;
	byte*				CGameCtnChallenge__CreateBlockClip_retnpos;

	byte*				CGameCtnChallenge__InitBuildArea_hookpos;
	byte*				CGameCtnChallenge__InitBuildArea_retnpos;

	byte*				CGameCtnChallenge__GetZoneAtPos_hookpos;

	byte*				CGameCtnChallenge__UpdateFieldUnitsForBlock_hookpos;
	byte*				CGameCtnChallenge__UpdateFieldUnitsForBlock_retnpos;

	byte*				CGameCtnCollection__GetZoneByBlockInfo;

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

	byte*				CTrackManiaEditor__ProcessCursor_hookpos1;
	byte*				CTrackManiaEditor__ProcessCursor_hookpos2;
	byte*				CTrackManiaEditor__ProcessCursor_hookpos3;

	byte*				CTrackManiaEditor__MoveCursorDown_hookpos;

	byte*				CTrackManiaEditorTerrain__FloorCursorPos_hookpos;
	byte*				CTrackManiaEditorTerrain__FloorCursorPos_retnpos;

	byte*				CTrackManiaEditorTerrain__CreateTerrainBlockAtPos_hookpos;
	byte*				CTrackManiaEditorTerrain__CreateTerrainBlockAtPos_retnpos;

	byte*				StringKey__Resolve;

private:
	byte*				FindOffsettedPattern	( byte* pPattern, uint uiPatternSize, int iOffset );
    byte*				FindOffsettedPattern	( byte* pPattern, byte* pMask, uint uiPatternSize, int iOffset );

    PatternFinder       m_PatternFinder;
};
