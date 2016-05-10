#include "StdInc.h"

namespace TrackMania
{

    CMwNod* CSystemFid::LoadNode ()
    {
        if ( m_pNode )
            return m_pNode;

        typedef void (CreateNodFromFid_t)(CMwNod** ppNod, CSystemFid* pFid, dword dwFlags);
        CreateNodFromFid_t* CreateNodFromFid = (CreateNodFromFid_t *)Address::Inst.CreateNodFromFid;

        CMwNod* pNod = NULL;
        CreateNodFromFid ( &pNod, this, 7 );
        pNod->AddRef ();
        return pNod;
    }

}
