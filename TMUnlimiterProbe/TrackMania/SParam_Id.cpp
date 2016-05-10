#include "StdInc.h"

namespace TrackMania
{

    SParam_Id::SParam_Id ( StringKey skId, dword field14, dword* pClassIDs, dword fieldC )
    {
        _asm
        {
            push fieldC
            push pClassIDs
            push field14
            lea eax, skId
            push eax
            mov ecx, this
            call Address::Inst.SParam_Id__ctor
        }
    }

}
