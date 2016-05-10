#include "StdInc.h"

namespace TrackMania
{

    _declspec(naked) void CTrackManiaEditorInterface::CreateArticleIcons ( void* pGameInterface, CGameCtnCollection* pCollection, CGameCtnDecoration* pDecoration, CGameCtnCollectorList* pCollectorList )
    {
        _asm jmp Address::Inst.CTrackManiaEditorInterface__CreateArticleIcons
    }

    CTrackManiaEditorIconPage* CTrackManiaEditorInterface::GetSelectedIconPage ()
    {
        if ( !m_bInSubPage )
            return NULL;

        CTrackManiaEditorIconPage* pIconPage = m_RootIconPages [ m_dwSelectedRootIconPageIdx ];

        if ( m_IconPagePath.Size () == 0 )
            return pIconPage;

        IconPagePathEntry* pLastPathEntry = m_IconPagePath [ m_IconPagePath.Size () - 1 ];
        if ( m_IconPagePath.Size () == 1 )
            return pIconPage->GetIcons () [ pLastPathEntry->GetIndex () ]->GetIconPage ();

        return pLastPathEntry->GetIcon ()->GetIconPage ()->GetIcons () [ pLastPathEntry->GetIndex () ]->GetIconPage ();
    }

    std::vector < int > CTrackManiaEditorInterface::GetSelectedIconPath () const
    {
        std::vector < int > result;
        if ( !m_bInSubPage )
            return result;

        result.push_back ( m_dwSelectedRootIconPageIdx );
        for ( int i = 0; i < m_IconPagePath.Size (); i++ )
        {
            result.push_back ( m_IconPagePath [ i ]->GetIndex () );
        }
        return result;
    }

    void CTrackManiaEditorInterface::SetSelectedIconPath ( const std::vector < int >& iconPath )
    {
        if ( iconPath.empty () )
        {
            m_bInSubPage = false;
            return;
        }

        for ( auto it = m_IconPagePath.Begin (); it != m_IconPagePath.End (); it++ )
        {
            delete *it;
        }
        m_IconPagePath.Clear ();

        m_bInSubPage = true;
        m_dwSelectedRootIconPageIdx = iconPath [ 0 ];
        CTrackManiaEditorIconPage* pIconPage = m_RootIconPages [ m_dwSelectedRootIconPageIdx ];
        for ( int i = 1; i < iconPath.size (); i++ )
        {
            IconPagePathEntry* pEntry = new IconPagePathEntry (
                pIconPage->GetParentIcon (),
                iconPath[i]
            );
            m_IconPagePath.Add ( pEntry );

            pIconPage = pIconPage->GetIcons () [ iconPath[i] ]->GetIconPage ();
        }
    }

}
