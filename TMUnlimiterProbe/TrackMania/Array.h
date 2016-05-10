#pragma once

namespace TrackMania
{

	template<typename T>
	class Array
	{
	public:
		dword				Size				() const
		{
			return m_dwSize;
		}

		T&					operator[]			( int index )
		{
			return pElems [ index ];
		}

		const T&			operator[]			( int index ) const
		{
			return pElems [ index ];
		}

	private:
		dword				m_dwSize;
		T*					pElems;
	};

}
