#pragma once

namespace TrackMania
{

	class StringKey : public Allocatable
	{
	public:
                        StringKey       ()
        {
            m_dwKey = -1;
        }

                        StringKey       ( const StringKey& other )
        {
            m_dwKey = other.m_dwKey;
        }

                        StringKey       ( dword dwKey )
        {
            m_dwKey = dwKey;
        }

                        StringKey       ( const char* psz );

        StringKey&      operator=       ( const StringKey& other )
        {
            m_dwKey = other.m_dwKey;
            return *this;
        }

        StringKey&      operator=       ( const char* psz );

        dword           GetKey          () const        { return m_dwKey; }
        void            SetKey          ( dword dwKey ) { m_dwKey = dwKey; }

		const char*     Resolve         () const;

        bool            operator==      ( const StringKey& other ) const
        {
            return m_dwKey == other.m_dwKey;
        }

        bool            operator!=      ( const StringKey& other ) const
        {
            return !(*this == other);
        }

        bool            operator==      ( const char* psz ) const
        {
            return !strcmp ( Resolve (), psz );
        }

        bool            operator!=      ( const char* psz ) const
        {
            return !(*this == psz);
        }

	private:
		dword           m_dwKey;
	};

}
