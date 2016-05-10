#pragma once

namespace TrackMania
{

    class CSystemFids : public CMwNod
    {
    public:
        CSystemFids*                GetParentFolder         () const        { return m_pParentFids; }
        CSystemFids*                GetDrive                () const        { return m_pFidsDrive; }
        List < CSystemFid* >&       GetFiles                ()              { return m_Fids; }
        List < CSystemFids* >&      GetFolders              ()              { return m_FidFolders; }

    protected:
        CSystemFids*                m_pParentFids;
        CSystemFids*                m_pFidsDrive;
        List < CSystemFid* >        m_Fids;
        List < CSystemFids* >       m_FidFolders;
        dword                       m_field34;
    };

}