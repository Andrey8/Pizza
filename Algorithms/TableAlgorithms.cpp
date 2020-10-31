#include "TableAlgorithms.h"

#include <algorithm>



bool Algorithms::TableAlgorithms::SplitTableIntoCrosses( int tableWidth, int tableHeight, std::vector< CrossCenterData > & outData )
{
    int const w = tableWidth;
    int const h = tableHeight;

    Base::Table< Data > table( w, h );
    for ( CrossCenterData & ccdata : outData )
    {
        int const i = ccdata.pos.row;
        int const j = ccdata.pos.column;

        table.SetItem( i, j, Data( CellType::CrossCenter, nullptr, &ccdata ) );
    }

    Base::Table< Data > tableCopy = table;
    if ( SearchCrossCenterForAllCells( tableCopy, { 1, 1 } ) )
    {
        table = tableCopy;

        return true;
    }

    return false;
}

bool Algorithms::TableAlgorithms::SearchCrossCenterForAllCells( Base::Table< Data > & table, TCPos start )
{    
    if ( TableIsFilled( table ) && TableFillingIsSatisfiedCapacities( table ) )
    {
        return true;
    }

    TCPosList const positions = GetAllNextPositions( table, start );
    for ( TCPos const & pos : positions )
    {
        Data data = table.GetItem( pos.row, pos.column );

        switch ( data.cellType )
        {
        case CellType::None :
        {
            std::list< CrossCenterData > const ccDatas = GetAllCrossCenterDatas( table );
            std::list< Data > const notccDatas = GetAllCellDataExceptCrossCenters( table );

            if ( !SetCrossCenterForCell( table, pos, Direction::Upper, ccDatas, notccDatas ) &&
                 !SetCrossCenterForCell( table, pos, Direction::Bottom, ccDatas, notccDatas ) &&
                 !SetCrossCenterForCell( table, pos, Direction::Right, ccDatas, notccDatas ) &&
                 !SetCrossCenterForCell( table, pos, Direction::Left, ccDatas, notccDatas ) )
            {
                SetCrossCenterDatasRespectively( table, std::vector< CrossCenterData >( ccDatas.begin(), ccDatas.end() ) );
                SetCellDataRespectivelyExceptCrossCenter( table, std::vector< Data >( notccDatas.begin(), notccDatas.end() ) );

                return false;
            }
            else
            {
                return true;
            }

            break;
        }
        case CellType::CrossCenter :
        {
            continue;

            break;
        }
        case CellType::CrossBranch :
        {
            continue;

            break;
        }
        }
    }

    if ( TableIsFilled( table ) && TableFillingIsSatisfiedCapacities( table ) )
    {
        return true;
    }

    return false;
}



Algorithms::TableAlgorithms::TCPos Algorithms::TableAlgorithms::GetNearestCrossCenter(
        Base::Table< Data > const & table, TCPos pos, Direction direction )
{
    int const w = table.GetWidth();
    int const h = table.GetHeight();

    switch ( direction )
    {
    case Direction::Upper :
    {
        for ( int i = pos.row + 1; i <= h; ++i )
        {
            Data tcdata = table.GetItem( i, pos.column );
            if ( tcdata.cellType == CellType::CrossCenter )
            {
                return { i, pos.column };
            }
        }

        break;
    }
    case Direction::Bottom :
    {
        for ( int i = pos.row - 1; i >= 1; --i )
        {
            Data tcdata = table.GetItem( i, pos.column );
            if ( tcdata.cellType == CellType::CrossCenter )
            {
                return { i, pos.column };
            }
        }

        break;
    }
    case Direction::Right :
    {
        for ( int j = pos.column + 1; j <= w; ++j )
        {
            Data tcdata = table.GetItem( pos.row, j );
            if ( tcdata.cellType == CellType::CrossCenter )
            {
                return { pos.row, j };
            }
        }

        break;
    }
    case Direction::Left :
    {
        for ( int j = pos.column - 1; j >= 1; --j )
        {
            Data tcdata = table.GetItem( pos.row, j );
            if ( tcdata.cellType == CellType::CrossCenter )
            {
                return { pos.row, j };
            }
        }

        break;
    }
    }

    return { 0, 0 };
}

Algorithms::TableAlgorithms::TCPosList Algorithms::TableAlgorithms::GetPositionsBetween( TCPos pos1, TCPos pos2 )
{
    if ( pos1.row == pos2.row )
    {
        int const row = pos1.row;

        int const minColumn = std::min( pos1.column, pos2.column );
        int const maxColumn = std::max( pos1.column, pos2.column );

        TCPosList result;
        for ( int j = minColumn + 1; j < maxColumn; ++j )
        {
            result.push_back( { row, j } );
        }

        return result;
    }
    else if ( pos1.column == pos2.column )
    {
        int const column = pos1.column;

        int const minRow = std::min( pos1.row, pos2.row );
        int const maxRow = std::max( pos1.row, pos2.row );

        TCPosList result;
        for ( int i = minRow + 1; i < maxRow; ++i )
        {
            result.push_back( { i, column } );
        }

        return result;
    }

    throw std::invalid_argument( "" );
}

bool Algorithms::TableAlgorithms::TableIsFilled( Base::Table< Data > const & table )
{
    for ( int i = 1; i <= table.GetHeight(); ++i )
    {
        for ( int j = 1; j <= table.GetWidth(); ++j )
        {
            if ( table.GetItem( i, j ).cellType == CellType::None )
            {
                return false;
            }
        }
    }

    return true;
}

bool Algorithms::TableAlgorithms::TableFillingIsSatisfiedCapacities( Base::Table< Data > const & table )
{
    for ( int i = 1; i <= table.GetHeight(); ++i )
    {
        for ( int j = 1; j <= table.GetWidth(); ++j )
        {
            Data tcdata = table.GetItem( i, j );

            if ( tcdata.cellType == CellType::CrossCenter )
            {
                CrossCenterData const * ccdata = tcdata.crossCenterData;

                if ( ccdata->count != ccdata->capacity )
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Algorithms::TableAlgorithms::CellsAreUnfilled( const Base::Table< Data > & table, TCPosList const & cells )
{        
    for ( TCPos pos : cells )
    {
        Data data = table.GetItem( pos.row, pos.column );

        if ( data.cellType != CellType::None )
        {
            return false;
        }
    }

    return true;
}

bool Algorithms::TableAlgorithms::CellsBelongToSameBranchOfCrossCenter(
        const Base::Table< Data > & table,
        const TCPosList & cells,
        const Data * crossCenter )
{
    for ( TCPos pos : cells )
    {
        Data data = table.GetItem( pos.row, pos.column );

        if ( data.crossCenter != crossCenter )
        {
            return false;
        }
    }

    return true;
}

bool Algorithms::TableAlgorithms::CellsBelongToSameBranch( const Base::Table< Data > & table, const TCPosList & cells )
{
    if ( cells.empty() )
    {
        return true;
    }

    TCPos pos1 = cells.front();
    Data data1 = table.GetItem( pos1.row, pos1.column );
    for ( TCPos pos : cells )
    {
        Data data = table.GetItem( pos.row, pos.column );

        if ( data.crossCenter != data1.crossCenter )
        {
            return false;
        }
    }

    return true;
}

bool Algorithms::TableAlgorithms::SetCrossCenterForCell(
        Base::Table< Data > & table,
        TCPos pos,
        Direction crossCenterDirection,
        std::list< CrossCenterData > const & ccDatas,
        std::list< Data > const & notccDatas )
{
    SetCrossCenterDatasRespectively( table, std::vector< CrossCenterData >( ccDatas.begin(), ccDatas.end() ) );
    SetCellDataRespectivelyExceptCrossCenter( table, std::vector< Data >( notccDatas.begin(), notccDatas.end() ) );

    TCPos nearestCCPos = GetNearestCrossCenter( table, pos, crossCenterDirection );

    if ( nearestCCPos == TCPos::GetNeutralValue() )
    {
        return false;
    }

    Data const * nearestCCDataPointer = &table.GetItem( nearestCCPos.row, nearestCCPos.column );
    CrossCenterData * ccData = nearestCCDataPointer->crossCenterData;

    Data newData( CellType::CrossBranch, nearestCCDataPointer, nullptr );

    switch ( crossCenterDirection )
    {
    case Direction::Upper :
    {
        TCPosList const betweenPositions = GetPositionsBetween( pos, nearestCCPos );
        if ( CellsAreUnfilled( table, betweenPositions ) )
        {
            if ( ccData->capacity < ccData->count + betweenPositions.size() + 1 )
            {
                return false;
            }

            ccData->bottomCells.push_back( pos );
            ++( ccData->count );

            for ( TCPos betweenPos : betweenPositions )
            {
                ccData->bottomCells.push_back( betweenPos );

                table.SetItem( betweenPos.row, betweenPos.column, newData );
            }
            ccData->count += betweenPositions.size();

            table.SetItem( pos.row, pos.column, newData );

            return SearchCrossCenterForAllCells( table, GetNextPosition( table, pos ) );
        }
        else if ( CellsBelongToSameBranchOfCrossCenter( table, betweenPositions, nearestCCDataPointer ) )
        {
            if ( ccData->capacity < ccData->count + 1 )
            {
                return false;
            }

            ccData->bottomCells.push_back( pos );
            ++( ccData->count );

            table.SetItem( pos.row, pos.column, newData );

            return SearchCrossCenterForAllCells( table, GetNextPosition( table, pos ) );
        }
        else
        {
            return false;
        }

        break;
    }
    case Direction::Bottom :
    {
        TCPosList const betweenPositions = GetPositionsBetween( pos, nearestCCPos );
        if ( CellsAreUnfilled( table, betweenPositions ) )
        {
            if ( ccData->capacity < ccData->count + betweenPositions.size() + 1 )
            {
                return false;
            }

            ccData->upperCells.push_back( pos );
            ++( ccData->count );

            for ( TCPos betweenPos : betweenPositions )
            {
                ccData->upperCells.push_back( betweenPos );

                table.SetItem( betweenPos.row, betweenPos.column, newData );
            }
            ccData->count += betweenPositions.size();

            table.SetItem( pos.row, pos.column, newData );

            return SearchCrossCenterForAllCells( table, GetNextPosition( table, pos ) );
        }
        else if ( CellsBelongToSameBranchOfCrossCenter( table, betweenPositions, nearestCCDataPointer ) )
        {
            if ( ccData->capacity < ccData->count + 1 )
            {
                return false;
            }

            ccData->upperCells.push_back( pos );
            ++( ccData->count );

            table.SetItem( pos.row, pos.column, newData );

            return SearchCrossCenterForAllCells( table, GetNextPosition( table, pos ) );
        }
        else
        {
            return false;
        }

        break;
    }
    case Direction::Right :
    {
        TCPosList const betweenPositions = GetPositionsBetween( pos, nearestCCPos );
        if ( CellsAreUnfilled( table, betweenPositions ) )
        {
            if ( ccData->capacity < ccData->count + betweenPositions.size() + 1 )
            {
                return false;
            }

            ccData->leftCells.push_back( pos );
            ++( ccData->count );

            for ( TCPos betweenPos : betweenPositions )
            {
                ccData->leftCells.push_back( betweenPos );

                table.SetItem( betweenPos.row, betweenPos.column, newData );
            }
            ccData->count += betweenPositions.size();

            table.SetItem( pos.row, pos.column, newData );

            return SearchCrossCenterForAllCells( table, GetNextPosition( table, pos ) );
        }
        else if ( CellsBelongToSameBranchOfCrossCenter( table, betweenPositions, nearestCCDataPointer ) )
        {
            if ( ccData->capacity < ccData->count + 1 )
            {
                return false;
            }

            ccData->leftCells.push_back( pos );
            ++( ccData->count );

            table.SetItem( pos.row, pos.column, newData );

            return SearchCrossCenterForAllCells( table, GetNextPosition( table, pos ) );
        }
        else
        {
            return false;
        }

        break;
    }
    case Direction::Left :
    {
        TCPosList const betweenPositions = GetPositionsBetween( pos, nearestCCPos );
        if ( CellsAreUnfilled( table, betweenPositions ) )
        {
            if ( ccData->capacity < ccData->count + betweenPositions.size() + 1 )
            {
                return false;
            }

            ccData->rightCells.push_back( pos );
            ++( ccData->count );

            for ( TCPos betweenPos : betweenPositions )
            {
                ccData->rightCells.push_back( betweenPos );

                table.SetItem( betweenPos.row, betweenPos.column, newData );
            }
            ccData->count += betweenPositions.size();

            table.SetItem( pos.row, pos.column, newData );

            return SearchCrossCenterForAllCells( table, GetNextPosition( table, pos ) );
        }
        else if ( CellsBelongToSameBranchOfCrossCenter( table, betweenPositions, nearestCCDataPointer ) )
        {
            if ( ccData->capacity < ccData->count + 1 )
            {
                return false;
            }

            ccData->rightCells.push_back( pos );
            ++( ccData->count );

            table.SetItem( pos.row, pos.column, newData );

            return SearchCrossCenterForAllCells( table, GetNextPosition( table, pos ) );
        }
        else
        {
            return false;
        }

        break;
    }
    }

    throw std::logic_error( "" );
}

void Algorithms::TableAlgorithms::ClearNextPositionsExceptCrossCenters( Base::Table< Data > & table, TCPos position )
{
    table.SetItem( position.row, position.column, Data() );

    for ( TCPos pos : GetAllNextPositions( table, position ) )
    {
        Data data = table.GetItem( pos.row, pos.column );
        if ( data.cellType == CellType::CrossBranch )
        {
            table.SetItem( pos.row, pos.column, Data() );
        }
    }
}

std::list< Algorithms::TableAlgorithms::Data > Algorithms::TableAlgorithms::GetAllCellDataExceptCrossCenters(
        const Base::Table<Algorithms::TableAlgorithms::Data> & table )
{
    std::list< Data > result;
    for ( int i = 1; i <= table.GetHeight(); ++i )
    {
        for ( int j = 1; j <= table.GetWidth(); ++j )
        {
            Data data = table.GetItem( i, j );
            if ( data.cellType != CellType::CrossCenter )
            {
                result.push_back( data );
            }
        }
    }

    return result;
}

void Algorithms::TableAlgorithms::SetCellDataRespectivelyExceptCrossCenter( Base::Table< Data > & table, const std::vector< Data > & datas )
{
    int index = 0;
    for ( int i = 1; i <= table.GetHeight(); ++i )
    {
        for ( int j = 1; j <= table.GetWidth(); ++j )
        {
            Data data = table.GetItem( i, j );
            if ( data.cellType != CellType::CrossCenter )
            {
                table.SetItem( i, j, datas[ index ] );

                ++index;
            }
        }
    }
}

std::list< Algorithms::TableAlgorithms::CrossCenterData > Algorithms::TableAlgorithms::GetAllCrossCenterDatas( const Base::Table< Data > & table )
{
    std::list< CrossCenterData > result;
    for ( int i = 1; i <= table.GetHeight(); ++i )
    {
        for ( int j = 1; j <= table.GetWidth(); ++j )
        {
            Data data = table.GetItem( i, j );
            if ( data.cellType == CellType::CrossCenter )
            {
                result.push_back( *( data.crossCenterData ) );
            }
        }
    }

    return result;
}

void Algorithms::TableAlgorithms::SetCrossCenterDatasRespectively( Base::Table< Data > & table, const std::vector< CrossCenterData > & datas )
{
    int index = 0;
    for ( int i = 1; i <= table.GetHeight(); ++i )
    {
        for ( int j = 1; j <= table.GetWidth(); ++j )
        {
            Data data = table.GetItem( i, j );
            if ( data.cellType == CellType::CrossCenter )
            {
                data.crossCenterData->count = datas[ index ].count;
                data.crossCenterData->upperCells = datas[ index ].upperCells;
                data.crossCenterData->bottomCells = datas[ index ].bottomCells;
                data.crossCenterData->rightCells = datas[ index ].rightCells;
                data.crossCenterData->leftCells = datas[ index ].leftCells;

                ++index;
            }
        }
    }
}



