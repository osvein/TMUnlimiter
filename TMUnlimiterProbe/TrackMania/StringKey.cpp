#include "StdInc.h"

namespace TrackMania
{

    StringKey::StringKey ( const char* psz )
    {
        *this = psz;
    }

	_declspec(naked) const char* StringKey::Resolve () const
	{
		_asm jmp Address::Inst.StringKey__Resolve
	}

    StringKey& StringKey::operator= ( const char* psz )
    {
        _asm
        {
            push psz
            mov ecx, this
            call Address::Inst.StringKey__Assign
        }
        return *this;
    }

}
