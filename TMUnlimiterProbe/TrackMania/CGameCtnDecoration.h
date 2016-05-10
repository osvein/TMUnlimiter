#pragma once

namespace TrackMania
{

	class CGameCtnDecoration : public CGameCtnCollector
	{
	public:
		CGameCtnDecorationSize*			GetSizeDecoration			() const
		{
			return m_pDecoSize;
		}

	private:
		CGameCtnDecorationSize*			m_pDecoSize;
		void*							m_pDecoAudio;
		void*							m_pDecoMood;
		void*							m_pDecoratorSolidWarp;
		void*							m_pTerrainModifierBase;
		void*							m_pTerrainModifierCovered;
	};

}
