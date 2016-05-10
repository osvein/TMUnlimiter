#pragma once

namespace TrackMania
{

	class CGameCtnEditor : public CMwNod
	{
	public:
		virtual void			mB0								() = 0;
		virtual void			mB4								() = 0;
		virtual void			mB8								() = 0;
		virtual void			mBC								() = 0;
		virtual void			mC0								() = 0;
		virtual void			mC4								() = 0;
		virtual void			mC8								() = 0;
		virtual void			mCC								() = 0;
		virtual void			mD0								() = 0;
		virtual void			mD4								() = 0;
		virtual void			mD8								() = 0;
		virtual void			mDC								() = 0;
		virtual void			DisconnectBlockUnitNeighbour	( CGameCtnBlockUnit* pUnit, int dir ) = 0;
		virtual void			mE4								() = 0;
		virtual void			ValidateBlockPositionAndPillars	() = 0;
		virtual void			ValidateBlockPillars			() = 0;
		virtual void			mF0								() = 0;
		virtual void			mF4								() = 0;
		virtual void			mF8								() = 0;
		virtual void			mFC								() = 0;
		virtual void			m100							() = 0;
		virtual void			m104							() = 0;
		virtual void			m108							() = 0;
		virtual void			PlaceBlock						() = 0;
		virtual void			AddBlock						() = 0;
		virtual void			RemoveBlockSafe					() = 0;
		virtual void			RemoveBlock						() = 0;
		virtual void			m11C							() = 0;
		virtual void			ClearAreaForBlock				() = 0;
		virtual void			m124							() = 0;
		virtual void			DisconnectDirFromRoadBlock		() = 0;
		virtual void			ConnectDirFromRoadBlock			() = 0;
		virtual void			m130							() = 0;
		virtual void			ConnectBlockToRoads				() = 0;
		virtual void			m138							() = 0;
		virtual void			m13C							() = 0;
		virtual void			m140							() = 0;

		CGameCtnChallenge*		GetChallenge					() const
		{
			return m_pChallenge;
		}

	private:
		dword					m_field14;
		dword					m_field18;
		dword					m_field1C;
		CGameCtnChallenge*		m_pChallenge;
		dword					m_field24;
		void*					m_pGridSceneMobil;
		dword					m_field2C;
		dword					m_field30;
		dword					m_field34;
		dword					m_dwEditorType;
		dword					m_field3C;
		dword					m_field40;
		dword					m_field44;
		dword					m_field48;
		dword					m_field4C;
		dword					m_field50;
		dword					m_field54;
		dword					m_field58;
		dword					m_field5C;
		dword					m_field60;
		dword					m_field64;
		dword					m_field68;
		dword					m_field6C;
		dword					m_field70;
		dword					m_field74;
		dword					m_field78;
		dword					m_field7C;
		dword					m_field80;
		dword					m_field84;
		dword					m_field88;
		dword					m_field8C;
		float					m_fMouseMoveDist;
		dword					m_field94;
		dword					m_field98;
	};

}

