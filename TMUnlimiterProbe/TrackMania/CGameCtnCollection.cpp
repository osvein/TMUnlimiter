#include "StdInc.h"

namespace TrackMania
{

	_declspec(naked) CGameCtnZone* CGameCtnCollection::GetZoneByBlockInfo ( CGameCtnBlockInfo* pBlockInfo ) const
	{
		_asm jmp Address::Inst.CGameCtnCollection__GetZoneByBlockInfo
	}

}
