#pragma once

namespace TrackMania
{

    class CTrackManiaEditor;

    class CTrackManiaEditorInterface : public CMwNod
    {
    public:
        CTrackManiaEditor*                      GetEditor               () const    { return m_pEditor; }

        void                                    CreateArticleIcons      ( void* pGameInterface, CGameCtnCollection* pCollection, CGameCtnDecoration* pDecoration, CGameCtnCollectorList* pCollectorList );
        List < CTrackManiaEditorIconPage* >&    GetRootIconPages        ()  { return m_RootIconPages; }

        CTrackManiaEditorIconPage*              GetSelectedIconPage     ();
        std::vector < int >                     GetSelectedIconPath     () const;
        void                                    SetSelectedIconPath     ( const std::vector < int >& iconPath );

    private:
        class IconPagePathEntry : public Allocatable
        {
        public:
                                        IconPagePathEntry   ( CTrackManiaEditorIcon* pIcon, dword dwIndex )
            {
                m_pIcon = NULL;
                m_dwIndex = -1;

                SetIcon ( pIcon );
                SetIndex ( dwIndex );
            }

                                        ~IconPagePathEntry  ()
            {
                if ( m_pIcon )
                    m_pIcon->Release ();
            }

            CTrackManiaEditorIcon*      GetIcon             () const { return m_pIcon; }
            dword                       GetIndex            () const { return m_dwIndex; }

            void                        SetIcon             ( CTrackManiaEditorIcon* pIcon )
            {
                if ( m_pIcon )
                    m_pIcon->Release ();

                m_pIcon = pIcon;
                if ( m_pIcon )
                    m_pIcon->AddRef ();
            }

            void                        SetIndex            ( dword dwIndex ) { m_dwIndex = dwIndex; }

        private:
            CTrackManiaEditorIcon*      m_pIcon;
            dword                       m_dwIndex;
        };

        dword                                   m_field14;
        dword                                   m_field18;
        StringW                                 m_field1C;
        void*                                   m_pSceneCamera;
        void*                                   m_pScene2D;
        dword                                   m_field2C;
        dword                                   m_field30;
        CTrackManiaEditor*                      m_pEditor;
        dword                                   m_bInSubPage;
        List < IconPagePathEntry* >             m_IconPagePath;
        dword                                   m_dwSelectedRootIconPageIdx;
        List < CTrackManiaEditorIconPage* >     m_RootIconPages;
        dword                                   m_field58;
        dword                                   m_field5C;
        dword                                   m_field60;
        dword                                   m_field64;
        Array < void* >                         m_ButtonPtrs;
        dword                                   m_field70;
        dword                                   m_field74;
        dword                                   m_field78;
        dword                                   m_field7C;
        dword                                   m_field80;
        dword                                   m_field84;
        dword                                   m_field88;
        dword                                   m_field8C;
    };

}
