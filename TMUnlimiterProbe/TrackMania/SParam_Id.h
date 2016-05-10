#pragma once

namespace TrackMania
{

    class SParam_Id : public SParam
    {
    public:
                        SParam_Id       ( StringKey skId, dword field14, dword* pClassIDs, dword fieldC );

        const char*     GetId           () const    { return m_skId.Resolve (); }
        dword           GetIdKey        () const    { return m_skId.GetKey (); }

    private:
        StringKey       m_skId;
        dword           m_field14;
    };

}
