#include "StdInc.h"

namespace TrackMania
{

    CGameCtnArticle* CGameCtnChapter::GetArticleByMeta ( const NodeMeta* pMeta )
    {
        for ( auto it = m_Articles.Begin (); it != m_Articles.End (); it++ )
        {
            if ( *(*it)->GetArticleMeta () == *pMeta )
                return *it;
        }
        return NULL;
    }

    CGameCtnCollection* CGameCtnChapter::GetCollection () const
    {
        if ( !m_pCollectionFid )
            return NULL;

        return (CGameCtnCollection *)m_pCollectionFid->GetNode ();
    }

    CGameCtnCollection* CGameCtnChapter::LoadCollection ()
    {
        if ( !m_pCollectionFid )
            return NULL;

        if ( m_pCollectionFid->GetNode () )
            return (CGameCtnCollection *)m_pCollectionFid->GetNode ();

        // Don't allocate on stack, otherwise our dummy destructor will be called instead
        // of TM's virtual one (optimization) which we don't want
        SParam_Id* pIdSParam = new SParam_Id ( "PlugSolidPackBrotherShaders", true, NULL, 0 );
        CSystemFidParameters* pFidParameters = new CSystemFidParameters ();
        pFidParameters->AddSParam ( pIdSParam );
        CSystemFidParameters::PushGlobalParameters ( pFidParameters, true );
        CGameCtnCollection* pCollection = (CGameCtnCollection *)m_pCollectionFid->LoadNode ();
        CSystemFidParameters::PopGlobalParameters ();
        delete pFidParameters;
        delete pIdSParam;

        pCollection->AddRef ();
        return pCollection;
    }

}
