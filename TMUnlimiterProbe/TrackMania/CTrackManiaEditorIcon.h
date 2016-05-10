#pragma once

namespace TrackMania
{

    class CTrackManiaEditorIconPage;

    class CTrackManiaEditorIcon : public CMwNod
    {
    public:
                                        CTrackManiaEditorIcon   ();
        virtual                         ~CTrackManiaEditorIcon  () {}

        CTrackManiaEditorIconPage*      GetIconPage             () const        { return m_pIconPage; }
        void                            SetIconPage             ( CTrackManiaEditorIconPage* pPage );

        CGameCtnArticle*                GetArticle              () const        { return m_pArticle; }
        void                            SetArticle              ( CGameCtnArticle* pArticle );

        CTrackManiaEditorIconPage*      GetParentIconPage       () const        { return m_pParentIconPage; }
        void                            SetParentIconPage       ( CTrackManiaEditorIconPage* pPage );

    private:
        CTrackManiaEditorIconPage*      m_pIconPage;
        CGameCtnArticle*                m_pArticle;
        CTrackManiaEditorIconPage*      m_pParentIconPage;
    };

}
