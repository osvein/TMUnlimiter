#pragma once

namespace TrackMania
{

    class CSystemFid;

    class SParam_Fid : public SParam_Fid_Common
    {
    public:
        CSystemFid*         GetFid          () const        { return m_pFid; }

    private:
        CSystemFid*         m_pFid;
    };

}
