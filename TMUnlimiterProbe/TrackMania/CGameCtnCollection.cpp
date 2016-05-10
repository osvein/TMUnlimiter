#include "StdInc.h"

namespace TrackMania
{

	CGameCtnZone* CGameCtnCollection::GetZoneByBlockInfo ( CGameCtnBlockInfo* pBlockInfo )
	{
        CGameCtnChapter* pChapter = CGameCtnCatalog::GetInstance ()->GetChapterByMeta ( pBlockInfo->GetBlockMeta () );
        if ( !pChapter )
            return NULL;

        CGameCtnCollection* pCollection = pChapter->LoadCollection ();
        if ( !pCollection )
            return NULL;

        CGameCtnZone* pZone = GetZoneFromListByBlockInfo ( pCollection->m_Zones1, pBlockInfo );
        if ( pZone )
            return pZone;

        pZone = GetZoneFromListByBlockInfo ( pCollection->m_Zones2, pBlockInfo );
        if ( pZone )
            return pZone;

        return NULL;
	}

    CGameCtnZone* CGameCtnCollection::GetZoneFromListByBlockInfo ( List < CGameCtnZone* >& list, CGameCtnBlockInfo* pBlockInfo )
    {
        for ( auto it = list.Begin (); it != list.End (); it++ )
        {
            CGameCtnBlockInfo* pZoneBlockInfo = NULL;
            if ( (*it)->GetType () == CGameCtnZone::FLAT )
                pZoneBlockInfo = ((CGameCtnZoneFlat *)*it)->GetFlatBlockInfo ();
            else if ( (*it)->GetType () == CGameCtnZone::FRONTIER )
                pZoneBlockInfo = ((CGameCtnZoneFrontier *)*it)->GetFrontierBlockInfo ();

            if ( pZoneBlockInfo == pBlockInfo )
                return *it;
        }
        return NULL;
    }

}
