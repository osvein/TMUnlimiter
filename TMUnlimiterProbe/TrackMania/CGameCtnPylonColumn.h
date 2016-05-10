#pragma once

namespace TrackMania
{

    class CGameCtnPylonColumn : public CMwNod
    {
    public:
        dword           GetBottomY          () const                { return m_dwBottomY; }
        dword           GetTopY             () const                { return m_dwTopY; }

        void            SetBottomY          ( dword dwBottomY )     { m_dwBottomY = dwBottomY; }
        void            SetTopY             ( dword dwTopY )        { m_dwTopY = dwTopY; }

    private:
        dword           m_dwBottomY;
        dword           m_dwTopY;
        dword           m_field1C;
        dword           m_field20;
        dword           m_field24;
        dword           m_field28;
    };

}
