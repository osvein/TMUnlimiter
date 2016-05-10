#pragma once

namespace TrackMania
{

	class NodeMeta : public Allocatable
	{
	public:
        bool            operator==              ( const NodeMeta& other ) const
        {
            return m_skUID == other.m_skUID && m_skEnvironment == other.m_skEnvironment;
        }

        bool            operator!=              ( const NodeMeta& other ) const
        {
            return !(*this == other);
        }

		StringKey       m_skUID;
		StringKey       m_skEnvironment;
		StringKey       m_skAuthor;
	};

}
