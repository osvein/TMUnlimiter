#pragma once

namespace TrackMania
{

    class CTrackManiaEditorIconPage : public CMwNod
    {
    public:
                                            CTrackManiaEditorIconPage   ();
        virtual                             ~CTrackManiaEditorIconPage  () {}

        const char*                         GetName                     () const    { return m_strName.CStr (); }
        List < CTrackManiaEditorIcon* >&    GetIcons                    ()          { return m_Icons; }
        CTrackManiaEditorIcon*              GetParentIcon               () const    { return m_pParentIcon; }
        CTrackManiaEditorIconPage*          GetIconPageByName           ( const char* pszName );

        void                                AddIcon                     ( CTrackManiaEditorIcon* pIcon );
        void                                RemoveIcon                  ( CTrackManiaEditorIcon* pIcon );
        void                                SetParentIcon               ( CTrackManiaEditorIcon* pIcon );

    private:
        StringA                             m_strName;
        List < CTrackManiaEditorIcon* >     m_Icons;
        dword                               m_field28;
        CTrackManiaEditorIcon*              m_pParentIcon;
    };

}
