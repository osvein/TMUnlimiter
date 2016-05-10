#pragma once

namespace TrackMania
{

    class SParam_Fid_Common : public SParam
    {
    protected:
        dword           m_dwNameHash;
        void*           m_pSystemPackDesc;
        StringA         m_strName;
        dword           m_dwClassID;
    };

}