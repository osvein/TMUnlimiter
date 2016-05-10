#include "StdInc.h"

namespace TrackMania
{

    CTrackManiaEditorIcon::CTrackManiaEditorIcon ()
    {
        _asm
        {
            mov ecx, this
            call Address::Inst.CTrackManiaEditorIcon__ctor
        }
    }

    void CTrackManiaEditorIcon::SetIconPage ( CTrackManiaEditorIconPage* pPage )
    {
        m_pIconPage = pPage;
        pPage->SetParentIcon ( this );
    }

    _declspec(naked) void CTrackManiaEditorIcon::SetArticle ( CGameCtnArticle* pArticle )
    {
        _asm jmp Address::Inst.CTrackManiaEditorIcon__SetArticle
    }

    void CTrackManiaEditorIcon::SetParentIconPage ( CTrackManiaEditorIconPage* pPage )
    {
        m_pParentIconPage = pPage;
    }

}
