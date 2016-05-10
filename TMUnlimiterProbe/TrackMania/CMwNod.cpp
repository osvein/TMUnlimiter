#include "StdInc.h"

namespace TrackMania
{

    _declspec(naked) void CMwNod::Release ()
    {
        _asm jmp Address::Inst.CMwNod__Release
    }

}
