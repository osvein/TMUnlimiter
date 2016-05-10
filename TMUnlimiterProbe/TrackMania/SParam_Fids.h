#pragma once

namespace TrackMania
{

    class CSystemFids;

    class SParam_Fids : public SParam_Fid_Common
    {
    public:
        CSystemFids*        GetFids             () const    { return m_pFids; }

    private:
        CSystemFids*        m_pFids;
    };

}
