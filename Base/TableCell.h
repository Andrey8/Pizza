#pragma once

namespace Base { template < typename T > class Table; }



namespace Base
{
    template < typename T >
    class TableCell
    {
    public:
        TableCell( T * data, Table< T > *, int i, int j );
        TableCell()
            : m_data( nullptr ),
              m_table( nullptr ),
              m_i( 0 ),
              m_j( 0 )
        {}

    private:
        T * m_data;
        Table< T > * m_table;
        int m_i;
        int m_j;
    };



    template < typename T >
    TableCell< T >::TableCell( T * data, Table< T > * table, int i, int j )
        : m_data( data ),
          m_table( table ),
          m_i( i ),
          m_j( j )
    {

    }
}
