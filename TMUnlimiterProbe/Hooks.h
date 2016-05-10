#pragma once

class Hooks
{
public:
	static void					Install									();

private:
	struct HookEntry
	{
		byte*					m_pHookPos;
		void*					m_pTarget;
	};

	static void					hook_ValidateBlockPositionAndPillars	();
	static bool					handle_ValidateBlockPositionAndPillars	();

	static void					hook_ClearAreaForBlock					();
	static bool					handle_ClearAreaForBlock				( TrackMania::CGameCtnBlock* pBlock );

	static void					hook_RemoveBlock						();
	static void					hook_RemoveBlockSafe					();
	static bool					handle_RemoveBlock						( TrackMania::CGameCtnEditor* pEditor, TrackMania::CGameCtnBlock* pRemovedBlock );

	static void					hook_IsBlockOnGround					();
	static int					handle_IsBlockOnGround					( TrackMania::CGameCtnBlockInfo* pBlockInfo );

	static void					hook_GetBlockUnitInfo					();
	static void*				handle_GetBlockUnitInfo					( TrackMania::CGameCtnBlockInfo* pBlockInfo, int index, bool bGround );

	static void					hook_CreateBlockClip					();
	static bool					handle_CreateBlockClip					( TrackMania::CGameCtnChallenge* pChallenge, TrackMania::Vec3Di pos );

	static void					hook_GetZoneAtPos						();
	static TrackMania::CGameCtnZone*	handle_GetZoneAtPos				( TrackMania::CGameCtnChallenge* pChallenge, TrackMania::Vec3Di pos );

	static void					hook_CreateRoadBlock					();
	static bool					handle_CreateRoadBlock					( TrackMania::CGameCtnEditor* pEditor, TrackMania::Vec3Di pos );

	static void					hook_InitBuildArea						();
	static void					handle_InitBuildArea					( TrackMania::CGameCtnChallenge* pChallenge );

	static void					hook_FloorCursorPos						();
	static bool					handle_FloorCursorPos					( TrackMania::CTrackManiaEditor* pEditor, TrackMania::Vec3Di* pPos );

	static void					hook_CreateTerrainBlockAtPos			();
	static void					handle_CreateTerrainBlockAtPos			( TrackMania::CTrackManiaEditor* pEditor, TrackMania::Vec3Di* pPos );
};
