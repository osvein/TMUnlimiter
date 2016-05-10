#pragma once

namespace TrackMania
{

	class CGameCtnBlock;

	class CGameCtnBlockUnit : public CMwNod
	{
	public:
		CGameCtnBlock*				GetBlock				() const
		{
			return m_pBlock;
		}

		CGameCtnBlockUnitInfo*		GetBlockUnitInfo		() const
		{
			return m_pBlockUnitInfo;
		}

		CGameCtnFieldUnit*			GetFieldUnit			() const
		{
			return m_pFieldUnit;
		}

		Vec3Di						GetOffset				() const
		{
			return m_Offset;
		}

		void						SetOffset				( Vec3Di offset )
		{
			m_Offset = offset;
		}

		Vec3Di						GetPosition				() const;

		int							NumClipBlockInfos		() const
		{
			return m_ClipBlockInfos.Size ();
		}

		CGameCtnBlockInfo*			GetClipBlockInfo		( int dir )
		{
			return m_ClipBlockInfos [ dir ];
		}

	private:
		CGameCtnBlock*				m_pBlock;
		CGameCtnBlockUnitInfo*		m_pBlockUnitInfo;
		CGameCtnFieldUnit*			m_pFieldUnit;
		Array<CGameCtnBlockInfo*>	m_ClipBlockInfos;
		Vec3Di						m_Offset;
		dword						m_field34;
		dword						m_field38;
	};

}
