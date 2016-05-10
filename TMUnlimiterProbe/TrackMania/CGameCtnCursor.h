#pragma once

namespace TrackMania
{

	class CGameCtnCursor : public CMwNod
	{
	public:
		Vec3Di			GetPosition				() const
		{
			return m_pos;
		}

	private:
		Vec3Di			m_pos;
		dword			m_field20;
		dword			m_field24;
		dword			m_field28;
		dword			m_field2C;
		dword			m_field30;
		dword			m_field34;
		dword			m_field38;
		dword			m_dwDir;
		void*			m_pBlockMobil;
		void*			m_pCursorMobil;
		void*			m_pBlockHelperMobil;
		dword			m_field4C;
		dword			m_field50;
		dword			m_field54;
		Color			m_CanPlaceColor;
		Color			m_CanJoinColor;
		Color			m_CannotPlaceNorJoinColor;
		Color			m_NothingToDoColor;
	};

}
