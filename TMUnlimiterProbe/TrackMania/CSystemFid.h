#pragma once

namespace TrackMania
{

    class CSystemFids;

    class CSystemFid : public CMwNod
    {
    public:
        CSystemFids*            GetFolder           () const        { return m_pParentFids; }
        CMwNod*                 GetNode             () const        { return m_pNode; }
        CMwNod*                 LoadNode            ();

        CSystemFid*             GetMainFid          () const        { return m_pMainFid; }
        List < CSystemFid* >&   GetParametrizedFids ()              { return m_ParametrizedFids; }

    protected:
        CSystemFids*            m_pParentFids;
        dword                   m_dwFlags1;
        dword                   m_dwFlags2;
        CMwNod*                 m_pNode;
        List < CSystemFid* >    m_ParametrizedFids;
        CSystemFid*             m_pMainFid;
        CSystemFidParameters    m_Parameters;
        dword                   m_dwClassID;
        void*                   m_pMetaDataEntries;
        void*                   m_pLoader;
        dword                   m_dwIndex;
    };

}
