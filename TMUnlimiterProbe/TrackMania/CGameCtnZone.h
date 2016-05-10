#pragma once

namespace TrackMania
{

	class CGameCtnZone : public CMwNod
	{
	private:
		StringKey			m_skName;
		StringKey			m_sk2;
		dword				m_bFrontier;
		dword				m_dwHeight;
		dword				m_dwDepth;
		dword				m_bOldZone;
		dword				m_bHasWater;
	};

}
