#pragma once

#include "TableCell.h"

#include <vector>
#include <stdexcept>



namespace Base
{
    template < typename T > using CellRow = std::vector< TableCell< T > >;

    template < typename T >
    class Table
    {
        using Cell = TableCell< T >;
    public:
        Table( int width, int height );
        Table( std::vector< std::vector< T > > const & data );

        T const & GetItem( int i, int j ) const;
        void SetItem( int i, int j, T const & value );

//        CellRow< T > const & operator[]( int i ) const;
//        CellRow< T > & operator[]( int i );

        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
    private:
        std::vector< CellRow< T > > m_cells;
        int m_width;
        int m_height;

        bool Check( std::vector< std::vector< T > > const & data );
    };



    template< typename T >
    Table< T >::Table( int width, int height )
        : m_cells( std::vector< CellRow< T > >( height ) ),
          m_width( width ),
          m_height( height )
    {
        for ( int i = 0; i < height; ++i )
        {
            CellRow< T > cellTempRow( width );
            for ( int j = 0; j < width; ++j )
            {
                cellTempRow[ j ] = TableCell< T >( T(), this, i, j );
            }
            m_cells[ i ] = cellTempRow;
        }
    }

    template< typename T >
    Table< T >::Table( std::vector< std::vector< T > > const & data )
    {
        if ( !Check( data ) )
        {
            throw std::invalid_argument( "Data can not be represented as a table." );
        }

        m_width = data.front().size();
        m_height = data.size();

        m_cells = std::vector< CellRow< T > >( m_height );
        for ( int i = 0; i < m_height; ++i )
        {
            CellRow< T > cellTempRow( m_width );
            for ( int j = 0; j < m_width; ++j )
            {
                cellTempRow[ j ] = TableCell< T >( data[ i ][ j ], this, i, j );
            }
            m_cells[ i ] = cellTempRow;
        }
    }

    template< typename T >
    T const & Table< T >::GetItem( int i, int j ) const
    {
        if ( i <= 0 || i > m_height || j <= 0 || j > m_width )
        {
            throw std::out_of_range( "" );
        }

        return ( m_cells[ i - 1 ][ j - 1 ].GetData() );
    }

    template< typename T >
    void Table< T >::SetItem( int i, int j, T const & value )
    {
        if ( i <= 0 || i > m_height || j <= 0 || j > m_width )
        {
            throw std::out_of_range( "ERROR : indices are out of range." );
        }

        m_cells[ i - 1 ][ j - 1 ] = value;
    }

//    template< typename T >
//    CellRow< T > const & Table< T >::operator[]( int i ) const
//    {
//        if ( i <= 0 || i > m_height )
//        {
//            throw std::out_of_range( "" );
//        }

//        return m_cells[ i - 1 ];
//    }

//    template< typename T >
//    CellRow< T > & Table< T >::operator[]( int i )
//    {
//        if ( i <= 0 || i > m_height )
//        {
//            throw std::out_of_range( "" );
//        }

//        return m_cells[ i - 1 ];
//    }

    template< typename T >
    bool Table< T >::Check( std::vector< std::vector< T > > const & data )
    {
        int const h = data.size();

        if ( h == 0 )
        {
            return false;
        }

        int const w = data[ 0 ].size();
        for ( int i = 1; i < h; ++i )
        {
            if ( data[ i ].size() != w )
            {
                return false;
            }
        }

        return true;
    }


}
