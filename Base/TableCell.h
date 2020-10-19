#pragma once

namespace Base { template < typenmae T > class Table; }



namespace Base
{
    template < typename T >
    class TableCell
    {
    public:
        TableCell( Table< T > *, int i, int j );

    };
}
