#include "StdInc.h"

namespace TrackMania
{
    CGameCtnCatalog* CGameCtnCatalog::GetInstance()
    {
        return (CGameCtnCatalog *)(*(dword *)Address::Inst.CGameCtnCatalog__Instance);
    }

    CGameCtnChapter* CGameCtnCatalog::GetChapterByMeta ( const NodeMeta* pMeta )
    {
        for ( auto it = m_Chapters.Begin (); it != m_Chapters.End (); it++ )
        {
            if ( (*it)->GetNameKey () == pMeta->m_skEnvironment.GetKey () )
                return *it;
        }
        return NULL;
    }

    CGameCtnArticle* CGameCtnCatalog::GetArticleByMeta ( const NodeMeta* pMeta )
    {
        CGameCtnChapter* pChapter = GetChapterByMeta ( pMeta );
        if ( !pChapter )
            return NULL;

        return pChapter->GetArticleByMeta ( pMeta );
    }

}
