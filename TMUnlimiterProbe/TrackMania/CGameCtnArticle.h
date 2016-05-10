#pragma once

namespace TrackMania
{

    class CGameCtnArticle : public CMwNod
    {
    public:
        CSystemFidFile*             GetCollectorFid             () const    { return m_pCollectorFid; }
        NodeMeta*                   GetArticleMeta              ()          { return &m_Meta; }
        List < StringA >&           GetPagePathParts            ()          { return m_PagePathParts; }

    private:
        CSystemFidFile*             m_pCollectorFid;
        NodeMeta                    m_Meta;
        void*                       m_pBitmapIcon;
        CGameCtnCollector::Chunk003 m_Chunk003;
        void*                       m_pGameSkin;
        dword                       m_field5C;
        dword                       m_field60;
        StringA                     m_strPagePath;
        List < StringA >            m_PagePathParts;
        dword                       m_dwFlags;
        dword                       m_dwNumAvailableCurrent;
        dword                       m_dwNumAvailableMax;
        dword                       m_field84;
        dword                       m_field88;
        void*                       m_pCurrentSkin;
        List < void* >              m_SkinPackDescs;
    };

}
