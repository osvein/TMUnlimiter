#pragma once

namespace TrackMania
{

	class StringW
	{
	public:
		dword				GetSize				() const
		{
			return m_dwSize;
		}

		wchar_t*			GetCStr				() const
		{
			return m_pwsz;
		}

	private:
		dword				m_dwSize;
		wchar_t*			m_pwsz;
	};

}