#include "StdInc.h"

namespace TrackMania
{

	_declspec(naked) char* StringKey::Resolve () const
	{
		_asm jmp Address::Inst.StringKey__Resolve
	}

}
