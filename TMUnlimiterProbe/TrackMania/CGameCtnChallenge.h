#pragma once

namespace TrackMania
{

	class CGameCtnChallenge : public CMwNod
	{
	public:
		bool								IsPosInBounds			( Vec3Di pos )
		{
			return pos.X >= 0 && pos.X < m_vecSize.X &&
				   pos.Y >= 0 && pos.Y < m_vecSize.Y &&
				   pos.Z >= 0 && pos.Z < m_vecSize.Z;
		}

		CGameCtnFieldUnit*					GetFieldUnitAtPos		( Vec3Di pos )
		{
			if ( !IsPosInBounds ( pos ) )
				return NULL;

			List<CGameCtnFieldUnit*>& fieldUnitsAtXZ = *m_FieldUnits [ pos.X*m_vecSize.Z + pos.Z ];
			if ( pos.Y >= fieldUnitsAtXZ.Size () )
				return NULL;

			return fieldUnitsAtXZ [ pos.Y ];
		}

		CGameCtnBlock*						GetBlockAtPos			( Vec3Di pos )
		{
			CGameCtnFieldUnit* pFieldUnit = GetFieldUnitAtPos ( pos );
			if ( !pFieldUnit || !pFieldUnit->GetBlockUnit () )
				return NULL;

			return pFieldUnit->GetBlockUnit ()->GetBlock ();
		}

		int									NumBlocks				() const
		{
			return m_Blocks.Size ();
		}

		CGameCtnBlock*						GetBlock				( int i )
		{
			if ( i < 0 || i >= m_Blocks.Size () )
				return NULL;

			return m_Blocks [ i ];
		}

		Vec3Di								GetBuildAreaSize		() const
		{
			return m_vecSize;
		}

		void								SetBuildAreaSize		( Vec3Di vecSize )
		{
			m_vecSize = vecSize;
		}

		CGameCtnCollection*					GetCollection			() const
		{
			return m_pCollection;
		}

		CGameCtnDecoration*					GetDecoration			() const
		{
			return m_pDecoration;
		}

	private:
		Array<List<CGameCtnFieldUnit*>*>	m_FieldUnits;
		Array<void*>						m_field1C;
		Array<void*>						m_field24;
		Array<void*>						m_field2C;
		Array<void*>						m_field34;
		Array<void*>						m_field3C;
		Array<byte>							m_GroundHeights;
		Array<void*>						m_field4C;
		List<CGameCtnBlock*>				m_Blocks;
		List<void*>							m_Checkpoints;
		List<CGameCtnBlock*>				m_BlocksPendingRemoval;
		List<void*>							m_field78;
		List<void*>							m_SceneMobils;
		CGameCtnCollection*					m_pCollection;
		CGameCtnBlockInfo*					m_pCurrentBlockInfo;
		void*								m_pUndergroundBox;
		void*								m_pSkinBox;
		void*								m_pUndergroundSceneMobil;
		void*								m_pSkinSceneMobil;
		Vec3Di								m_vecSize;
		void*								m_pChallengeParameters;
		dword								m_dwNeedUnlock;
		dword								m_fieldBC;
		dword								m_fieldC0;
		NodeMeta							m_Meta;
		void*								m_pCollectorList;
		dword								m_bIsBlockHelpers;
		dword								m_fieldD8;
		NodeMeta							m_Meta2;
		NodeMeta							m_Meta3;
		dword								m_fieldF4;
		dword								m_dwPlayMode;
		dword								m_dwDifficulty;
		dword								m_dwNumLaps;
		dword								m_dwCopperPrice;
		StringW								m_wstrChallengeName;
		dword								m_dwKind;
		CGameCtnDecoration*					m_pDecoration;
		// ...
	};

}
