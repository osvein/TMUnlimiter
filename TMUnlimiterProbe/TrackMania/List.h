#pragma once

namespace TrackMania
{

	template<typename T>
	class List : public Array<T>
	{
	public:
                            List                    ()
        {
            m_pBuffer = NULL;
            m_dwSize = 0;
            m_dwCapacity = 0;
        }

                            List                    ( const List < T >& other )
        {
            m_pBuffer = NULL;
            m_dwSize = 0;
            m_dwCapacity = 0;

            *this = other;
        }

                            ~List                   ()
        {
            if ( m_pBuffer )
                Allocatable::operator delete ( m_pBuffer );

            m_pBuffer = NULL;
            m_dwSize = 0;
            m_dwCapacity = 0;
        }

        List < T >&         operator=               ( const List < T >& other )
        {
            Clear ();
            Reserve ( other.Size () );
            AddRange ( other );
            return *this;
        }

        void                Reserve                 ( dword dwNewCapacity )
        {
            assert ( dwNewCapacity > 0 );
            if ( dwNewCapacity < m_dwCapacity )
                return;

            T* pNewBuffer = (T *)( (byte *)Allocatable::operator new(sizeof(dword) + dwNewCapacity*sizeof(T)) + sizeof(dword) );
            *((dword *)pNewBuffer - 1) = dwNewCapacity;
            if ( m_pBuffer )
            {
                for ( int i = 0; i < m_dwSize; i++ )
                {
                    new (&pNewBuffer[i]) T ( m_pBuffer[i] );
                    m_pBuffer[i].~T ();
                }
                Allocatable::operator delete ( (dword *)m_pBuffer - 1 );
            }

            m_pBuffer = pNewBuffer;
            m_dwCapacity = dwNewCapacity;
        }

        void                Resize              ( dword dwNewSize )
        {
            if ( dwNewSize > m_dwCapacity )
            {
                dword dwNewCapacity = m_dwCapacity;
                if ( dwNewCapacity == 0 )
                    dwNewCapacity = 1;

                while ( dwNewSize > dwNewCapacity )
                {
                    dwNewCapacity *= 2;
                }
                Reserve ( dwNewCapacity );
            }

            for ( int i = m_dwSize; i < dwNewSize; i++ )
            {
                new (&m_pBuffer[i]) T ();
            }
            for ( int i = dwNewSize; i < m_dwSize; i++ )
            {
                m_pBuffer[i].~T ();
            }
            m_dwSize = dwNewSize;
        }

        void                SetSize             ( dword dwNewSize )
        {
            m_dwSize = dwNewSize;
        }

        void                Add                 ( const T& item )
        {
            Insert ( item, m_dwSize );
        }

        void                AddRange            ( const List < T >& other )
        {
            for ( int i = 0; i < other.Size (); i++ )
            {
                Add ( other[i] );
            }
        }

        void                Insert              ( const T& item, int index )
        {
            Resize ( m_dwSize + 1 );
            for ( int i = m_dwSize - 1; i > index; i-- )
            {
                m_pBuffer [ i ] = m_pBuffer [ i - 1 ];
            }
            m_pBuffer [ index ] = item;
        }

        bool                Remove              ( const T& item )
        {
            int index = IndexOf ( item );
            if ( index < 0 )
                return false;

            RemoveAt ( index );
            return true;
        }

        void                RemoveAt            ( int index )
        {
            assert ( index >= 0 && index < m_dwSize );
            for ( int i = index; i < m_dwSize - 1; i++ )
            {
                m_pBuffer [ i ] = m_pBuffer [ i + 1 ];
            }
            Resize ( m_dwSize - 1 );
        }

        int                 IndexOf             ( const T& item ) const
        {
            for ( int i = 0; i < m_dwSize; i++ )
            {
                if ( m_pBuffer [ i ] == item )
                    return i;
            }
            return -1;
        }

        void                Clear               ()
        {
            Resize ( 0 );
        }

        class iterator
        {
        public:
                            iterator            ( const iterator& other )
            {
                *this = other;
            }

            iterator&       operator=           ( const iterator& other )
            {
                m_pList = other.m_pList;
                m_iIndex = other.m_iIndex;
                return *this;
            }

            T&              operator*           ()
            {
                assert ( m_iIndex >= 0 && m_iIndex < m_pList->Size () );
                return (*m_pList) [ m_iIndex ];
            }

            T*              operator->          ()
            {
                return &(**this);
            }

            bool            operator==          ( const iterator& other ) const
            {
                return m_pList == other.m_pList && m_iIndex == other.m_iIndex;
            }

            bool            operator!=          ( const iterator& other ) const
            {
                return !(*this == other);
            }

            bool            operator<           ( const iterator& other ) const
            {
                assert ( m_pList == other.m_pList );
                return m_iIndex < other.m_iIndex;
            }

            bool            operator<=          ( const iterator& other ) const
            {
                assert ( m_pList == other.m_pList );
                return m_iIndex <= other.m_iIndex;
            }

            bool            operator>           ( const iterator& other ) const
            {
                return !(*this <= other);
            }

            bool            operator>=          ( const iterator& other ) const
            {
                return !(*this < other);
            }

            iterator&       operator++          ()
            {
                assert ( m_iIndex < m_pList->Size () );
                m_iIndex++;
                return *this;
            }

            iterator        operator++          ( int )
            {
                iterator result ( *this );
                ++*this;
                return result;
            }

            iterator&       operator--          ()
            {
                assert ( m_iIndex > 0 );
                m_iIndex--;
                return *this;
            }

            iterator        operator--          ( int )
            {
                iterator result ( *this );
                --*this;
                return result;
            }

        private:
            friend List < T >;

                            iterator            ( List < T >* pList, int iIndex )
                                : m_pList ( pList ), m_iIndex ( iIndex )
                            {
                            }

            List < T >*     m_pList;
            int             m_iIndex;
        };

        iterator            Begin               ()
        {
            return iterator ( this, 0 );
        }

        iterator            End                 ()
        {
            return iterator ( this, Size () );
        }

	private:
		dword				m_dwCapacity;
	};

}
