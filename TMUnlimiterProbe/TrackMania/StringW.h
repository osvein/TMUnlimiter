#pragma once

namespace TrackMania
{

	class StringW : public Allocatable
	{
	public:
		dword				Size				() const
		{
			return m_dwSize;
		}

		wchar_t*			CStr				() const
		{
			return m_pwsz;
		}

	private:
		dword				m_dwSize;
		wchar_t*			m_pwsz;
	};

}