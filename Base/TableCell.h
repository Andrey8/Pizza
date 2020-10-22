#pragma once

namespace Base { template < typename T > class Table; }



namespace Base
{
    template < typename T >
    class TableCell
    {
    public:
        TableCell( T const & data, Table< T > * table, int i, int j )
            : m_data( data ),
              m_table( table ),
              m_i( i ),
              m_j( j )
        {}
        TableCell()
            : m_data( T() ),
              m_table( nullptr ),
              m_i( 0 ),
              m_j( 0 )
        {}

        TableCell< T > const & operator=( T const & data )
        {
            m_data = data;

            return *this;
        }

        T const & GetData() const { return m_data; }
        void SetData( T const & data ) { m_data = data; }

    private:
        T m_data;
        Table< T > * m_table;
        int m_i;
        int m_j;
    };



}
