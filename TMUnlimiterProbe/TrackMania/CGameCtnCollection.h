#pragma once

namespace TrackMania
{

	class CGameCtnCollection : public CMwNod
	{
	public:
		const char*             GetEnvironmentName          () const    { return m_skEnvironment.Resolve (); }
        dword                   GetEnvironmentNameKey       () const    { return m_skEnvironment.GetKey (); }

		static CGameCtnZone*    GetZoneByBlockInfo			( CGameCtnBlockInfo* pBlockInfo );

		CGameCtnZone*			GetDefaultZone				() const    { return m_pDefaultZone; }

        float                   GetSquareSize               () const    { return m_fSquareSize; }
        float                   GetSquareHeight             () const    { return m_fSquareHeight; }

	private:
        static CGameCtnZone*    GetZoneFromListByBlockInfo  ( List < CGameCtnZone* >& list, CGameCtnBlockInfo* pBlockInfo );

		List < CGameCtnZone* >  m_CompleteZoneList;
		List < CGameCtnZone* >  m_Zones1;
		List < CGameCtnZone* >  m_Zones2;
		CGameCtnZone*			m_pDefaultZone;
		dword					m_field3C;
		dword					m_field40;
		StringKey				m_skEnvironment;
		StringW					m_wstrDisplayName;
		List<void*>				m_ArticleList;
		dword					m_dwNeedUnlock;
		NodeMeta				m_Meta;
		CGameCtnDecoration*		m_pDefaultDecoration;
		dword					m_field70;
		dword					m_field74;
		dword					m_field78;
		float					m_fSquareSize;
		float					m_fSquareHeight;
		dword					m_dwBlocksShadow;
		float					m_fShadowSoftSizeInWorld;
		dword					m_bShadowCastBlack;
		dword					m_dwBackgroundShadow;
		float					m_fWaterTop;
		float					m_fWaterBottom;
		dword					m_bIsWaterOutsidePlayField;
		dword					m_bIsWaterMultiHeight;
		float					m_fCameraMinHeight;
		dword					m_bCarCanBeDirty;
		dword					m_dwVertexLighting;
		float					m_fColorVertexMin;
		float					m_fColorVertexMax;
		dword					m_bIsEditable;
		dword					m_dwCollectionType;
		void*					m_pIconFid;
		void*					m_pIconSmallFid;
		void*					m_pLoadScreenFid;
		dword					m_dwSortIndex;
		void*					m_pMapFid;
		dword					m_fieldD4;
		dword					m_fieldD8;
		dword					m_fieldDC;
		dword					m_fieldE0;
		Vec2D					m_vecMapCoordElem;
		Vec2D					m_vecMapCoordIcon;
		Vec2D					m_vecMapCoordDesc;
		StringW					m_wstrLongDesc;
		void*					m_pFolderBlockInfo;
		void*					m_pFolderObjectInfo;
		void*					m_pFolderDecoration;
		void*					m_pFolderMenusIcons;
		List<void*>				m_field114;
		List<void*>				m_field120;
		List<void*>				m_BaseZoneStrings;
		List<void*>				m_ReplacementZoneStrings;
		List<void*>				m_ReplacementTerrainModifiers;
		List<void*>				m_ParticleEmitterModelsFids;
		List<void*>				m_field15C;
	};

}
