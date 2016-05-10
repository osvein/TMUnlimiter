#pragma once

namespace Hooks
{

    class HooksBase
    {
    public:
                                    HooksBase               () {}
        virtual                     ~HooksBase              () {}

        virtual void                Init                    () = 0;

    protected:
        struct HookEntry
        {
            byte*					m_pHookPos;
            void*					m_pTarget;
        };

        void                        InstallHooks            ( HookEntry* pHookEntries );
    };

}
