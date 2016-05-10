#pragma once

namespace TrackMania
{

    class Allocatable
    {
    public:
        void*           operator new                ( size_t size );
        void*           operator new                ( size_t size, void* ptr );

        void            operator delete             ( void* ptr );
    };

}
