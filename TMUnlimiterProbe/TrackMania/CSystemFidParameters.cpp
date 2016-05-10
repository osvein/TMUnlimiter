#include "StdInc.h"

namespace TrackMania
{

    CSystemFidParameters::CSystemFidParameters ()
    {
        _asm
        {
            mov ecx, this
            call Address::Inst.CSystemFidParameters__ctor
        }
    }

    int CSystemFidParameters::GetNumSParamsOfType ( SParam::eType type )
    {
        return m_Ranges [ type ].m_ucLength;
    }

    SParam* CSystemFidParameters::GetSParam ( SParam::eType type, int iIndex )
    {
        assert ( iIndex >= 0 && iIndex < m_Ranges [ type ].m_ucLength );
        return m_Params [ m_Ranges[type].m_ucOffset + iIndex ];
    }

    _declspec(naked) void CSystemFidParameters::AddSParam ( SParam* pSParam )
    {
        _asm jmp Address::Inst.CSystemFidParameters__AddSParam
    }

    _declspec(naked) void CSystemFidParameters::PushGlobalParameters ( CSystemFidParameters* pParams, bool bInheritDefaultParameters )
    {
        _asm jmp Address::Inst.PushSystemFidParameters
    }

    void CSystemFidParameters::PopGlobalParameters ()
    {
        List < CSystemFidParameters* >* pPtrList = (List<CSystemFidParameters*>*)Address::Inst.CSystemFidParameters__PtrList;
        List < CSystemFidParameters >* pList = (List<CSystemFidParameters>*)Address::Inst.CSystemFidParameters__List;

        pPtrList->SetSize ( pPtrList->Size () - 1 );
        pList->SetSize ( pList->Size () - 1 );
    }

}
