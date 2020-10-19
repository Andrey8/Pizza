#pragma once

#include <array>

namespace Base { template < typename T > class TableCell; }



namespace Base
{
    template < typename T >
    class Table
    {
    public:
        //using Row = std::array< TableCell< T > >;

        Table( int width, int height ) {}
        Table( T ** data );



        int GetWidth() const;
        int GetHeight() const;
    private:

    };

    template < typename T, int w, int h >
    class ConstSizeTable : public Table< T >
    {
    public:
        using Row = std::array< TableCell< T >, w >;

        Table( T ** data );

        Row const & operator[]( int i );
    };



    void TestTables()
    {
        Table< int > t1( 3, 5 );
    }
}
