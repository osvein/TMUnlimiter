#pragma once

namespace TrackMania
{

    class CSystemFidParameters : public Allocatable
    {
    public:
                                CSystemFidParameters            ();
        virtual                 ~CSystemFidParameters           () { assert ( !"Must use TrackMania destructor" ); }

        struct Range
        {
            byte                m_ucOffset;
            byte                m_ucLength;
        };

        int                     GetNumSParamsOfType             ( SParam::eType type );
        SParam*                 GetSParam                       ( SParam::eType type, int iIndex );

        void                    AddSParam                       ( SParam* pSParam );

        static void             PushGlobalParameters            ( CSystemFidParameters* pParams, bool bInheritDefaultParameters );
        static void             PopGlobalParameters             ();

    private:
        List < Range >          m_Ranges;
        List < SParam* >        m_Params;
        dword                   m_field1C;
        dword                   m_field20;
        dword                   m_field24;
        dword                   m_field28;
        dword                   m_field2C;
    };

}