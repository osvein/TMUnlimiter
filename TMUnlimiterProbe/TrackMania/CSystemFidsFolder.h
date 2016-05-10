#pragma once

namespace TrackMania
{

    class CSystemFidsFolder : public CSystemFids
    {
    public:
        const wchar_t*      GetName         () const        { return m_wstrName.CStr (); }

    protected:
        dword               m_field38;
        dword               m_field3C;
        StringW             m_wstrName;
    };

}
