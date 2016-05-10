#pragma once

namespace TrackMania
{

	class CGameCtnZone : public CMwNod
	{
    public:
        enum eType
        {
            FLAT,
            FRONTIER
        };

        const char*         GetName                 () const    { return m_skName.Resolve (); }
        eType               GetType                 () const    { return m_Type; }

	private:
		StringKey			m_skName;
		StringKey			m_sk2;
		eType				m_Type;
		dword				m_dwHeight;
		dword				m_dwDepth;
		dword				m_bOldZone;
		dword				m_bHasWater;
	};

}
