#pragma once

namespace TrackMania
{

    class CGameCtnZoneFlat : public CGameCtnZone
    {
    public:
        CGameCtnBlockInfo*          GetFlatBlockInfo            () const        { return m_pBlockInfoFlat; }
        CGameCtnBlockInfo*          GetClipBlockInfo            () const        { return m_pBlockInfoClip; }
        CGameCtnBlockInfo*          GetRoadBlockInfo            () const        { return m_pBlockInfoRoad; }
        CGameCtnBlockInfo*          GetPylonBlockInfo           () const        { return m_pBlockInfoPylon; }

        void                        SetFlatBlockInfo            ( CGameCtnBlockInfo* pBlockInfo );
        void                        SetClipBlockInfo            ( CGameCtnBlockInfo* pBlockInfo );
        void                        SetRoadBlockInfo            ( CGameCtnBlockInfo* pBlockInfo );
        void                        SetPylonBlockInfo           ( CGameCtnBlockInfo* pBlockInfo );

    private:
        CGameCtnBlockInfo*          m_pBlockInfoFlat;
        CGameCtnBlockInfo*          m_pBlockInfoClip;
        CGameCtnBlockInfo*          m_pBlockInfoRoad;
        CGameCtnBlockInfo*          m_pBlockInfoPylon;
        dword                       m_bGroundOnly;
    };

}
