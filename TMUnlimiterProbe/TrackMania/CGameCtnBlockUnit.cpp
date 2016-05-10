#include "StdInc.h"

namespace TrackMania
{

	Vec3Di CGameCtnBlockUnit::GetPosition () const
	{
		return m_pBlock->GetPosition () + GetOffset ();
	}

}
