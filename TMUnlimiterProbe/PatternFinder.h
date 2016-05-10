#pragma once

class PatternFinder
{
public:
    static void                 Init            ( void* pBase, uint uiSize );
    static void*                Find            ( byte* pPattern, uint uiSize );
    static void*                Find            ( byte* pPattern, byte* pMask, uint uiSize );

private:
    static byte*                m_pBase;
    static uint                 m_uiSize;
};
