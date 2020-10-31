#pragma once

#include "../Base/Table.h"

#include <vector>
#include <list>



namespace Algorithms
{
    namespace TableAlgorithms
    {
        enum class CellType
        {
            CrossCenter,
            CrossBranch,
            None
        };

        enum class Direction
        {
            Upper,
            Bottom,
            Right,
            Left
        };

        struct TableCellPosition
        {
            int row;
            int column;

            bool operator==( TableCellPosition const & other )
            {
                return ( row == other.row && column == other.column );
            }

            bool operator!=( TableCellPosition const & other )
            {
                return !( *this == other );
            }

            static TableCellPosition GetNeutralValue()
            {
                return { 0, 0 };
            }
        };
        using TCPos = TableCellPosition;
        using TCPosList = std::list< TCPos >;

        struct CrossCenterData
        {
            CrossCenterData( TCPos position, int cap )
                : pos( position ),
                  capacity( cap ),
                  count( 0 )
            {}

            TCPos pos;
            int capacity;

            int count;
            TCPosList upperCells;
            TCPosList bottomCells;
            TCPosList rightCells;
            TCPosList leftCells;
        };

        struct TableCellData
        {
            TableCellData( CellType ct, TableCellData const * cc, CrossCenterData * ccdata )
                : cellType( ct ),
                  crossCenter( cc ),
                  crossCenterData( ccdata )
            {}

            TableCellData()
                : cellType( CellType::None ),
                  crossCenter( nullptr ),
                  crossCenterData( nullptr )
            {}

            CellType cellType;
            TableCellData const * crossCenter;
            CrossCenterData * crossCenterData;
        };
        using Data = TableCellData;

        struct TableCellData2
        {
            TableCellData2( CellType ct, TCPos ccPos, CrossCenterData ccData )
                : cellType( ct ),
                  crossCenterPos( ccPos ),
                  crossCenterData( ccData )
            {}

            TableCellData2()
                : cellType( CellType::None ),
                  crossCenterPos( TCPos::GetNeutralValue() ),
                  crossCenterData( TCPos::GetNeutralValue(), -1 )
            {}

            CellType cellType;
            TCPos crossCenterPos;
            CrossCenterData crossCenterData;
        };
        using Data_2 = TableCellData2;



        bool SplitTableIntoCrosses(
                int tableWidth, int tableHeight, std::vector< CrossCenterData > & outData );
        bool SearchCrossCenterForAllCells(
                Base::Table< Data > &, TCPos start );
        bool SetCrossCenterForCell(
                Base::Table< Data > &, TCPos cellPos, Direction,
                std::list< CrossCenterData > const & ccDatas,
                std::list< Data > const & notccDatas );

        template < typename T >
        TCPosList GetAllNextPositions(
                Base::Table< T > const & table, TCPos start );

        template < typename T >
        TCPos GetNextPosition(
                Base::Table< T > const & table, TCPos pos );

        std::list< Data > GetAllCellDataExceptCrossCenters(
                Base::Table< Data > const & table );
        void SetCellDataRespectivelyExceptCrossCenter(
                Base::Table< Data > & table, std::vector< Data > const & datas );
        std::list< CrossCenterData > GetAllCrossCenterDatas(
                Base::Table< Data > const & table );
        void SetCrossCenterDatasRespectively(
                Base::Table< Data > & table, std::vector< CrossCenterData > const & datas );
        void ClearNextPositionsExceptCrossCenters(
                Base::Table< Data > & table, TCPos pos );
        TCPos GetNearestCrossCenter(
                Base::Table< Data > const & table, TCPos pos, Direction direction );
        TCPosList GetPositionsBetween(
                TCPos pos1, TCPos pos2 );

        bool TableIsFilled( Base::Table< Data > const & table );
        bool TableFillingIsSatisfiedCapacities(
                Base::Table< Data > const & table );
        bool CellsAreUnfilled(
                Base::Table< Data > const & table, const TCPosList & cells );
        bool CellsBelongToSameBranchOfCrossCenter(
                Base::Table< Data > const & table, const TCPosList & cells, Data const * crossCenter );
        bool CellsBelongToSameBranch(
                Base::Table< Data > const & table, const TCPosList & cells );
    }
}



template < typename T >
Algorithms::TableAlgorithms::TCPosList Algorithms::TableAlgorithms::GetAllNextPositions(
        Base::Table< T > const & table, TCPos pos )
{
    int const w = table.GetWidth();
    int const h = table.GetHeight();

    TCPosList result;
    for ( int j = pos.column; j <= w; ++j )
    {
        result.push_back( { pos.row, j } );
    }

    for ( int i = pos.row + 1; i <= h; ++i )
    {
        for ( int j = 1; j <= w; ++j )
        {
            result.push_back( { i, j } );
        }
    }

    return result;
}

template< typename T >
Algorithms::TableAlgorithms::TCPos Algorithms::TableAlgorithms::GetNextPosition( const Base::Table< T > & table, TCPos pos )
{
    int const w = table.GetWidth();
    int const h = table.GetHeight();

    if ( pos.column < w )
    {
        return { pos.row, pos.column + 1 };
    }
    else
    {
        if ( pos.row < h )
        {
            return { pos.row + 1, 1 };
        }

        return TCPos::GetNeutralValue();
    }
}

