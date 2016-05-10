#include "StdInc.h"

namespace TrackMania
{
    
    CTrackManiaEditorIconPage::CTrackManiaEditorIconPage ()
    {
        _asm
        {
            mov ecx, this
            call Address::Inst.CTrackManiaEditorIconPage__ctor
        }
    }

    CTrackManiaEditorIconPage* CTrackManiaEditorIconPage::GetIconPageByName ( const char* pszName )
    {
        for ( auto it = m_Icons.Begin (); it != m_Icons.End (); it++ )
        {
            if ( (*it)->GetIconPage () && !strcmp ( (*it)->GetIconPage ()->GetName (), pszName ) )
                return (*it)->GetIconPage ();
        }
        return NULL;
    }

    void CTrackManiaEditorIconPage::AddIcon ( CTrackManiaEditorIcon* pIcon )
    {
        if ( m_Icons.Contains ( pIcon ) )
            return;

        pIcon->SetParentIconPage ( this );
        m_Icons.Add ( pIcon );
        pIcon->AddRef ();
    }

    void CTrackManiaEditorIconPage::RemoveIcon ( CTrackManiaEditorIcon* pIcon )
    {
        if ( m_Icons.Remove ( pIcon ) )
            pIcon->Release ();
    }

    void CTrackManiaEditorIconPage::SetParentIcon ( CTrackManiaEditorIcon* pIcon )
    {
        m_pParentIcon = pIcon;
    }

}
