#pragma once

namespace TrackMania
{

	class CGameCtnCollector : public CMwNod
	{
	public:
        struct Chunk003
        {
        public:
            NodeMeta            m_Meta;
            StringA             m_strPagePath;
            StringKey           m_sk1;
            short               m_id;
            byte                m_field1A;
            byte                m_field1B;
            dword               m_field1C;
            short               m_field20;
            short               m_field22;
            StringKey           m_sk2;
            StringKey           m_sk3;
            byte                m_flags;
            byte                m_field2D;
            byte                m_field2E;
            byte                m_field2F;
        };

        const NodeMeta*         GetBlockMeta            () const        { return &m_Meta; }

	private:
		StringA					m_strFolder;
		CSystemFidFile*         m_pIconFid;
		dword					m_field20;
		NodeMeta				m_Meta;
		dword					m_field30;
		dword					m_field34;
		dword					m_field38;
		dword					m_field3C;
		dword					m_field40;
		dword					m_field44;
		dword					m_SK1;
		dword					m_SK2;
		dword					m_field50;
		dword					m_field54;
	};

}
