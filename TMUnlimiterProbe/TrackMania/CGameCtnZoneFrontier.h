#pragma once

namespace TrackMania
{

    class CGameCtnZoneFrontier : public CGameCtnZone
    {
    public:
        CGameCtnBlockInfo*          GetFrontierBlockInfo            () const        { return m_pBlockInfoFrontier; }

    private:
        CGameCtnBlockInfo*          m_pBlockInfoFrontier;
        StringKey                   m_sk1;
        StringKey                   m_sk2;
    };

}
