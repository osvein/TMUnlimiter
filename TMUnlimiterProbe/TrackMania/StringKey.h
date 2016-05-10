#pragma once

namespace TrackMania
{

	class StringKey
	{
	public:
		char*			Resolve					() const;

	private:
		dword			m_dwKey;
	};

}
