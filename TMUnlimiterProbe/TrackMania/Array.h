#pragma once

namespace TrackMania
{

	template<typename T>
	class Array : public Allocatable
	{
	public:
		dword				Size				() const
		{
			return m_dwSize;
		}

		T&					operator[]			( int index )
		{
			return m_pBuffer [ index ];
		}

		const T&			operator[]			( int index ) const
		{
			return m_pBuffer [ index ];
		}

        bool                Contains            ( const T& item ) const
        {
            for ( int i = 0; i < m_dwSize; i++ )
            {
                if ( (*this)[i] == item )
                    return true;
            }
            return false;
        }

    protected:
		dword				m_dwSize;
		T*					m_pBuffer;
	};

}
