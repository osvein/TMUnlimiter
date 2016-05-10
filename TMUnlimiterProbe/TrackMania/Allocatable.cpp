#include "StdInc.h"

namespace TrackMania
{

    _declspec(naked) void* Allocatable::operator new ( size_t size )
    {
        _asm jmp Address::Inst.operator_new;
    }

    void* Allocatable::operator new ( size_t size, void* ptr )
    {
        return ptr;
    }

    _declspec(naked) void Allocatable::operator delete ( void* ptr )
    {
        _asm jmp Address::Inst.operator_delete;
    }

}
