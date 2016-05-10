#pragma once

namespace TrackMania
{

	class StringA : public Allocatable
	{
	public:
                            StringA             ();
                            StringA             ( const char* psz );
                            StringA             ( const StringA& other );
                            ~StringA            ();

		dword				Size				() const        { return m_dwSize; }
		char*				CStr				() const        { return m_psz; }

        StringA&            operator=           ( const char* psz );
        StringA&            operator=           ( const StringA& other );

        bool                operator==          ( const char* psz );
        bool                operator==          ( const StringA& other );

        bool                operator!=          ( const char* psz )         { return !(*this == psz); }
        bool                operator!=          ( const StringA& other )    { return !(*this == other); }

        void                Reserve             ( dword dwCapacity, bool bKeepContent = true, char** ppOrigSz = NULL );
        void                Resize              ( dword dwSize );
        void                Clear               ();

	private:
		dword				m_dwSize;
		char*				m_psz;
	};

}
