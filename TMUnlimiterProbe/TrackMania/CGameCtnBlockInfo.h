#pragma once

namespace TrackMania
{

	class CGameCtnBlockInfo : public CGameCtnCollector
	{
	public:
		enum eType
		{
			BLOCKTYPE_FLAT,
			BLOCKTYPE_FRONTIER,
			BLOCKTYPE_CLASSIC,
			BLOCKTYPE_ROAD,
			BLOCKTYPE_CLIP,
			BLOCKTYPE_SLOPE,
			BLOCKTYPE_PYLON,
			BLOCKTYPE_RECTASYM
		};

		enum eWaypointType
		{
			WAYPOINT_START,
			WAYPOINT_FINISH,
			WAYPOINT_CHECKPOINT,
			WAYPOINT_NONE,
			WAYPOINT_STARTFINISH
		};

		eType							GetType						() const
		{
			return m_Type;
		}

		eWaypointType					GetWaypointType				() const
		{
			return m_WaypointType;
		}

		Array<CGameCtnBlockUnitInfo*>&	GetGroundBlockUnitInfos		()
		{
			return m_GroundBlockUnitInfos;
		}

		Array<CGameCtnBlockUnitInfo*>&	GetAirBlockUnitInfos		()
		{
			return m_AirBlockUnitInfos;
		}

	private:
		dword							m_field58;
		dword							m_field5C;
		dword							m_field60;
		dword							m_field64;
		dword							m_field68;
		dword							m_field6C;
		dword							m_field70;
		dword							m_field74;
		dword							m_field78;
		eType							m_Type;
		Iso4							m_SpawnLocGround;
		Iso4							m_SpawnLocAir;
		dword							m_bIsPillar;
		dword							m_bIsReplacement;
		dword							m_selection;
		Array<CGameCtnBlockUnitInfo*>	m_GroundBlockUnitInfos;
		Array<CGameCtnBlockUnitInfo*>	m_AirBlockUnitInfos;
		Array<void*>					m_GroundSceneMobilLists;
		Array<void*>					m_AirSceneMobilLists;
		void*							m_pPillars;
		void*							m_pGroundHelperMobil;
		void*							m_pAirHelperMobil;
		void*							m_pConstructionHelperMobil;
		eWaypointType					m_WaypointType;
		dword							m_bNoRespawn;
		dword							m_field124;
		dword							m_SK;
		dword							m_field12C;
	};

}
