#include "StdInc.h"

namespace TrackMania
{

    void CGameCtnZoneFlat::SetFlatBlockInfo ( CGameCtnBlockInfo* pBlockInfo )
    {
        if ( m_pBlockInfoFlat )
            m_pBlockInfoFlat->Release ();

        m_pBlockInfoFlat = pBlockInfo;

        if ( m_pBlockInfoFlat )
            m_pBlockInfoFlat->AddRef ();
    }

    void CGameCtnZoneFlat::SetClipBlockInfo ( CGameCtnBlockInfo* pBlockInfo )
    {
        if ( m_pBlockInfoClip )
            m_pBlockInfoClip->Release ();

        m_pBlockInfoClip = pBlockInfo;

        if ( m_pBlockInfoClip )
            m_pBlockInfoClip->AddRef ();
    }

    void CGameCtnZoneFlat::SetRoadBlockInfo ( CGameCtnBlockInfo* pBlockInfo )
    {
        if ( m_pBlockInfoRoad )
            m_pBlockInfoRoad->Release ();

        m_pBlockInfoRoad = pBlockInfo;

        if ( m_pBlockInfoRoad )
            m_pBlockInfoRoad->AddRef ();
    }

    void CGameCtnZoneFlat::SetPylonBlockInfo ( CGameCtnBlockInfo* pBlockInfo )
    {
        if ( m_pBlockInfoPylon )
            m_pBlockInfoPylon->Release ();

        m_pBlockInfoPylon = pBlockInfo;

        if ( m_pBlockInfoPylon )
            m_pBlockInfoPylon->AddRef ();
    }

}
