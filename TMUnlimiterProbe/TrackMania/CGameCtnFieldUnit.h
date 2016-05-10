#pragma once

namespace TrackMania
{

	class CGameCtnBlockUnit;

	class CGameCtnFieldUnit
	{
	public:
		virtual						~CGameCtnFieldUnit				() = 0;

		CGameCtnBlockUnit*			GetBlockUnit					() const
		{
			return m_pBlockUnit;
		}

		void						SetBlockUnit					( CGameCtnBlockUnit* pBlockUnit )
		{
			m_pBlockUnit = pBlockUnit;
		}

		dword						GetType							() const
		{
			return m_dwType;
		}

	private:
		CGameCtnBlockUnit*			m_pBlockUnit;
		dword						m_dwType;
	};

}
