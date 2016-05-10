#pragma once

namespace TrackMania
{

    class CSystemFidsFolder;

    class CSystemFidFile : public CSystemFid
    {
    public:
        const wchar_t*      GetName                 () const        { return m_wstrName.CStr (); }

    protected:
        StringW             m_wstrName;
        dword               m_dwIndex;
        dword               m_dwSizeLow;
        dword               m_dwSizeHigh;
    };

}
