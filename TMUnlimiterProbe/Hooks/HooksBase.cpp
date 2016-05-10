#include "StdInc.h"

namespace Hooks
{

    void HooksBase::InstallHooks ( HookEntry* pHookEntries )
    {
        for ( HookEntry* pHookEntry = pHookEntries; pHookEntry->m_pHookPos; pHookEntry++ )
        {
            *pHookEntry->m_pHookPos = 0xE9;
            *(dword *)(pHookEntry->m_pHookPos + 1) = (byte *)pHookEntry->m_pTarget - (pHookEntry->m_pHookPos + 5);
        }
    }

}
