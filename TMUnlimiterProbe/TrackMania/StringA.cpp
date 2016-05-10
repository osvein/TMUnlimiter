#include "StdInc.h"

namespace TrackMania
{

    StringA::StringA ()
    {
        m_dwSize = 0;
        m_psz = (char *)Address::Inst.StringA__pszEmpty;
    }

    StringA::StringA ( const char* psz )
    {
        m_dwSize = 0;
        m_psz = (char *)Address::Inst.StringA__pszEmpty;
        *this = psz;
    }

    StringA::StringA ( const StringA& other )
    {
        m_dwSize = 0;
        m_psz = (char *)Address::Inst.StringA__pszEmpty;
        *this = other;
    }

    StringA::~StringA ()
    {
        Clear ();
    }

    StringA& StringA::operator= ( const char* psz )
    {
        int iLen = strlen ( psz );
        Resize ( iLen );
        memcpy ( m_psz, psz, iLen );
        return *this;
    }

    StringA& StringA::operator= ( const StringA& other )
    {
        Resize ( other.Size () );
        memcpy ( m_psz, other.m_psz, other.Size () );
        return *this;
    }

    bool StringA::operator== ( const char* psz )
    {
        return strcmp ( psz, m_psz ) == 0;
    }

    bool StringA::operator== ( const StringA& other )
    {
        return other.m_dwSize == m_dwSize && !memcmp ( other.m_psz, m_psz, m_dwSize );
    }

    _declspec(naked) void StringA::Reserve ( dword dwCapacity, bool bKeepContent, char** ppOrigSz )
    {
        _asm jmp Address::Inst.StringA__Reserve
    }

    void StringA::Resize ( dword dwSize )
    {
        if ( dwSize == m_dwSize )
            return;

        Reserve ( dwSize );
        m_dwSize = dwSize;
        m_psz [ m_dwSize ] = '\0';
    }

    void StringA::Clear ()
    {
        if ( !m_psz || m_psz == (char *)Address::Inst.StringA__pszEmpty )
            return;

        typedef void (operator_delete_t) ( void* ptr );
        operator_delete_t* operator_delete = (operator_delete_t *)Address::Inst.operator_delete;
        if ( m_psz[-1] & 0x80 )
            operator_delete ( m_psz - 4 );
        else
            operator_delete ( m_psz - 1 );

        m_psz = (char *)Address::Inst.StringA__pszEmpty;
        m_dwSize = 0;
    }

}
