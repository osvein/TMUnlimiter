#pragma once

namespace TrackMania
{

    class CGameCtnCatalog : public CMwNod
    {
    public:
        static CGameCtnCatalog*     GetInstance         ();

        List < CGameCtnChapter* >&  GetChapters         ()      { return m_Chapters; }
        CGameCtnChapter*            GetChapterByMeta    ( const NodeMeta* pMeta );
        CGameCtnArticle*            GetArticleByMeta    ( const NodeMeta* pMeta );

    protected:
        List < NodeMeta >           m_ChapterAndArticleMetas;
        List < CGameCtnChapter* >   m_Chapters;
        void*                       m_pCollectorList;
    };

}
