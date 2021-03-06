#pragma once

namespace TrackMania
{

	class CTrackManiaEditor : public CGameCtnEditor
	{
	public:
		CGameCtnCursor*			    GetCursor			() const { return m_pCursor; }

        CTrackManiaEditorInterface* GetEditorInterface  () const { return m_pEditorInterface; }

	private:
		dword					    m_field9C;
		float					    m_fMinX;
		float					    m_fMaxX;
		float					    m_fMinZ;
		float					    m_fMaxZ;
		float					    m_fCamAngle;
		dword					    m_fieldB4;
		CTrackManiaEditorInterface* m_pEditorInterface;
		CGameCtnCursor*			    m_pCursor;
		dword					    m_fieldC0;
		void*					    m_pEditorLink;
		// ...
	};

}
