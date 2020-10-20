#pragma once

#include "TableCell.h"

//#include <array>
#include <vector>
//#include <list>

//namespace Base { template < typename T > class TableCell; }



namespace Base
{
    template < typename T > using Row = std::vector< TableCell< T > >;

    template < typename T >
    class Table
    {
        using Cell = TableCell< T >;
    public:
        Table( int width, int height );
        Table( std::vector< Row< T > > const & data );

        Row< T > const & operator[]( int i ) const;
        Row< T > & operator[]( int i );

        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
    private:
        std::vector< Row< T > > m_cells3;
        int m_width;
        int m_height;

        bool Check( std::vector< Row< T > > const & data );
    };



    template< typename T >
    Table< T >::Table( int width, int height )
        : m_cells3( std::vector< Row< T > >( height ) ),
          m_width( width ),
          m_height( height )
    {
        for ( int i = 0; i < height; ++i )
        {
            Row< T > cellTempRow( width );
            for ( int j = 0; j < width; ++j )
            {
                cellTempRow[ j ] = TableCell< T >( nullptr, this, i, j );
            }
            m_cells3[ i ] = cellTempRow;
        }
    }

    template< typename T >
    Table< T >::Table( std::vector< Row< T > > const & data )
    {
        if ( !Check( data ) )
        {
            throw std::exception();
        }

        m_width = data.front().size();
        m_height = data.size();

        m_cells3 = std::vector< Row< T > >( m_height );
        for ( int i = 0; i < m_height; ++i )
        {
            Row< T > cellTempRow( m_width );
            for ( int j = 0; j < m_width; ++j )
            {
                cellTempRow[ j ] = TableCell< T >( &data[ i ][ j ], this, i, j );
            }
            m_cells3[ i ] = cellTempRow;
        }
    }

    template< typename T >
    Row< T > const & Table< T >::operator[]( int i ) const
    {
        return m_cells3[ i ];
    }

    template< typename T >
    Row< T > & Table< T >::operator[]( int i )
    {
        return m_cells3[ i ];
    }

    template< typename T >
    bool Table< T >::Check( std::vector< Row< T > > const & data )
    {
        return true;
    }



    void TestTables()
    {
        Table< int > t1( 3, 5 );
    }
}
