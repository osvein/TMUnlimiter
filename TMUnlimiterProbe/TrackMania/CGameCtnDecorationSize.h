#pragma once

namespace TrackMania
{

	class CGameCtnDecorationSize : public CMwNod
	{
	public:
		Vec3Di			GetSize				() const
		{
			return m_vecSize;
		}

		void			SetSize				( Vec3Di vecSize )
		{
			m_vecSize = vecSize;
		}

	private:
		Vec2D			m_vecEditionZoneMin;
		Vec2D			m_vecEditionZoneMax;
		void*			m_pScene;
		dword			m_field28;
		Vec3Di			m_vecSize;
		int				m_iBaseHeight;
		int				m_iVertexCount;
		List<void*>		m_field40;
	};

}
