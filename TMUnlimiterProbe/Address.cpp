#include "StdInc.h"

Address Address::Inst;

Address::Address ()
{
	CodeBase = (byte *)0x401000;
	CodeSize = 0x727000;

	m_PatternFinder.Init ( CodeBase, CodeSize );

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

	static byte patUpdateFieldUnitsForBlock[] = {
		0x89, 0x6C, 0x24, 0x2C, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x0C, 0x07, 0x00, 0x00
	};
	byte* CGameCtnChallenge__UpdateFieldUnitsForBlock = FindOffsettedPattern ( patUpdateFieldUnitsForBlock,
		sizeof(patUpdateFieldUnitsForBlock), 0x37 );
	CGameCtnChallenge__UpdateFieldUnitsForBlock_hookpos = CGameCtnChallenge__UpdateFieldUnitsForBlock + 0x3F;
	CGameCtnChallenge__UpdateFieldUnitsForBlock_retnpos = CGameCtnChallenge__UpdateFieldUnitsForBlock + 0x74B;

	static byte patGetZoneByBlockInfo[] = {
		0x83, 0xC6, 0x01, 0x3B, 0xF3, 0x72, 0xD1, 0x8D, 0x7D, 0x2C
	};
	CGameCtnCollection__GetZoneByBlockInfo = FindOffsettedPattern ( patGetZoneByBlockInfo,
		sizeof(patGetZoneByBlockInfo), 0x40 );

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

	static byte patProcessCursor[] = {
		0x85, 0xC0, 0x0F, 0x85, 0x1D, 0x04, 0x00, 0x00, 0x39, 0xB5, 0x7C, 0x04,
		0x00, 0x00, 0x74, 0x0D
	};
	byte* CTrackManiaEditor__ProcessCursor = FindOffsettedPattern ( patProcessCursor,
		sizeof(patProcessCursor), 0xB8 );
	CTrackManiaEditor__ProcessCursor_hookpos1 = CTrackManiaEditor__ProcessCursor + 0x1297;
	CTrackManiaEditor__ProcessCursor_hookpos2 = CTrackManiaEditor__ProcessCursor + 0x12D3;
	CTrackManiaEditor__ProcessCursor_hookpos3 = CTrackManiaEditor__ProcessCursor + 0x212A;

	static byte patMoveCursorDown[] = {
		0x0F, 0x86, 0x00, 0x01, 0x00, 0x00, 0x8B, 0x46, 0x48, 0x83, 0xC1, 0xFF
	};
	byte* CTrackManiaEditor__MoveCursorDown = FindOffsettedPattern ( patMoveCursorDown,
		sizeof(patMoveCursorDown), 0x10 );
	CTrackManiaEditor__MoveCursorDown_hookpos = CTrackManiaEditor__MoveCursorDown + 0x90;

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

	static byte patStringKeyResolve[] = {
		0x81, 0xF9, 0x00, 0x00, 0x00, 0x80, 0x74, 0x03, 0x33, 0xC0, 0xC3, 0x25, 0xFF, 0xFF, 0xFF, 0x3F
	};
	StringKey__Resolve = FindOffsettedPattern ( patStringKeyResolve, sizeof(patStringKeyResolve), 0x12 );
}

byte* Address::FindOffsettedPattern ( byte* pPattern, uint uiPatternSize, int iOffset )
{
    void* pResult = m_PatternFinder.Find ( pPattern, uiPatternSize );
    if ( !pResult )
	{
		MessageBox ( NULL, "Could not find the code to patch. Please make sure your TrackMania is up to date (2.11.26 or later).",
			"TMUnlimiter", MB_ICONEXCLAMATION );
		ExitProcess ( 0 );
	}
    return (byte *)pResult - iOffset;
}
