#pragma once

namespace TrackMania
{

    class SParam : public Allocatable
    {
    public:
        virtual             ~SParam             ()                  { assert ( !"Must use TrackMania destructor" ); }
        virtual bool        m4                  ()                  { return false; }
        virtual SParam*     Clone               ()                  { return NULL; }
        virtual void        Assign              ( SParam* pSParam ) {}
        virtual void        Compare             ( SParam* pOther, bool* pbEqual, bool* pbDifferent )    {}

        enum eType
        {
            BITMAP,
            FID,
            ID,
            SET,
            GPUFX,
            SHADERFLAGS,
            SKIPSAMPLER1,
            SKIPSAMPLER2,
            FUNCSHADER,
            FIDS
        };

        eType               GetType             () const            { return m_dwType; }

    protected:
        eType               m_dwType;
        dword*              m_pdwClassIDs;
        dword               m_fieldC;
    };

}
