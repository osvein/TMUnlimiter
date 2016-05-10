#pragma once

namespace TrackMania
{

	class CGameCtnBlock : public CMwNod
	{
	public:
        NodeMeta*                   GetBlockMeta            ()          { return &m_Meta; }
		CGameCtnBlockInfo*			GetBlockInfo			() const    { return m_pBlockInfo; }
		Vec3Di						GetPosition				() const    { return m_pos; }
		dword						GetRotation				() const    { return m_dwRot; }
		dword						GetFlags				() const    { return m_dwFlags; }

		void						SetPosition				( Vec3Di pos )      { m_pos = pos; }
		void						SetRotation				( dword dwRot )     { m_dwRot = dwRot; }
		void						SetFlags				( dword dwFlags )   { m_dwFlags = dwFlags; }

		int							NumBlockUnits			() const            { return m_BlockUnits.Size (); }
        CGameCtnBlockUnit*			GetBlockUnit			( int i ) const     { return m_BlockUnits [ i ]; }

		bool						OccupiesPosition		( Vec3Di pos ) const
		{
			for ( int i = 0; i < NumBlockUnits (); i++ )
			{
				if ( GetBlockUnit ( i )->GetPosition () == pos )
					return true;
			}
			return false;
		}

	private:
		NodeMeta					m_Meta;
		CMwNod*						m_pCustomNode;
		CGameCtnBlockInfo*			m_pBlockInfo;
		Array<CGameCtnBlockUnit*>	m_BlockUnits;
		void*						m_pSceneMobil1;
		dword						m_field34;
		List<void*>					m_ExtraSceneMobils;
		void*						m_pSceneMobil2;
		Vec3Di						m_pos;
		dword						m_dwRot;
		dword						m_field58;
		dword						m_dwSK;
		dword						m_dwFlags;
	};

}
