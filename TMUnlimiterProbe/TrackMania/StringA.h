#pragma once

namespace TrackMania
{

	class StringA
	{
	public:
		dword				Size				() const
		{
			return m_dwSize;
		}

		char*				CStr				() const
		{
			return m_psz;
		}

	private:
		dword				m_dwSize;
		char*				m_psz;
	};

}
