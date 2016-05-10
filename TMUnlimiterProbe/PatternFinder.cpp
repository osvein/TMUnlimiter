#include "StdInc.h"

byte* PatternFinder::m_pBase;
uint  PatternFinder::m_uiSize;

void PatternFinder::Init ( void* pBase, uint uiSize )
{
    m_pBase = (byte *)pBase;
    m_uiSize = uiSize;
}

void* PatternFinder::Find ( byte* pPattern, uint uiSize )
{
    if ( uiSize == 0 || uiSize > m_uiSize )
        return NULL;

    byte* pSearch = m_pBase;
    byte* pEnd    = m_pBase + m_uiSize - uiSize + 1;
    for ( ; pSearch < pEnd; pSearch++ )
    {
        if ( pSearch[0] == pPattern[0] && !memcmp ( pSearch, pPattern, uiSize ) )
            return pSearch;
    }

    return NULL;
}

void* PatternFinder::Find ( byte* pPattern, byte* pMask, uint uiSize )
{
    if ( uiSize == 0 || uiSize > m_uiSize )
        return NULL;

    // Find the offset of the first nonzero mask byte, we will start comparing here
    uint uiOffset = 0;
    for ( ; uiOffset < uiSize; uiOffset++ )
    {
        if ( pMask [ uiOffset ] )
            break;
    }
    if ( uiOffset == uiSize )
        return NULL;

    pPattern += uiOffset;
    pMask    += uiOffset;
    uiSize   -= uiOffset;

    byte* pSearch = m_pBase + uiOffset;
    byte* pEnd    = m_pBase + m_uiSize - uiSize + 1;

    // Perform the search
    for ( ; pSearch < pEnd; pSearch++ )
    {
        if ( pSearch[0] == pPattern[0] )
        {
            bool bFound = true;
            for ( uint i = 0; i < uiSize/4; i++ )
            {
                if ( ( ((dword *)pSearch)[i] & ((dword *)pMask)[i] ) != ((dword *)pPattern)[i] )
                {
                    bFound = false;
                    break;
                }
            }

            if ( bFound )
            {
                for ( uint i = uiSize & ~3; i < uiSize; i++ )
                {
                    if ( ( pSearch[i] & pMask[i] ) != pPattern[i] )
                    {
                        bFound = false;
                        break;
                    }
                }
            }

            if ( bFound )
                return pSearch - uiOffset;
        }
    }

    // Nothing found
    return NULL;
}
