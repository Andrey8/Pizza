#include "Utils.h"
#include "../Algorithms/TableAlgorithms.h"

#include <fstream>



void OutputCreator::Utilities::HandleAndWriteData( const std::list< InputHandler::Data::CityData > & data, const std::string & outputFilePath )
{
    using CityData = InputHandler::Data::CityData;
    using PizzeriaData = InputHandler::Data::PizzeriaData;
    using CCData = Algorithms::TableAlgorithms::CrossCenterData;

    std::ofstream outFile;
    outFile.open( outputFilePath );

    if ( !outFile.is_open() )
    {
        throw std::runtime_error( "File has not opened for writing." );
    }

    int caseNumber = 1;
    for ( CityData const & cityData : data )
    {
        int const width = cityData.GetWidth();
        int const height = cityData.GetHeight();

        int const pizzeriasCount = cityData.GetPizzeriasData().size();
        std::vector< CCData > crossCenterData( pizzeriasCount );
        int i = 0;
        for ( PizzeriaData const & pizzeriaData : cityData.GetPizzeriasData() )
        {
            int const row = pizzeriaData.y;
            int const column = pizzeriaData.x;

            crossCenterData[ i ] = CCData( { row, column }, pizzeriaData.capacity );

            ++i;
        }

        if ( Algorithms::TableAlgorithms::SplitTableIntoCrosses(
                    width, height, crossCenterData ) )
        {
            outFile << "Case " << caseNumber << " :\n" ;

            for ( CCData const & ccdata : crossCenterData )
            {
                outFile << ccdata.upperCells.size()
                        << " "
                        << ccdata.rightCells.size()
                        << " "
                        << ccdata.bottomCells.size()
                        << " "
                        << ccdata.leftCells.size()
                        << "\n" ;
            }
        }
        else
        {
            outFile << "It's impossible to split the city for that input data." ;
        }

        outFile << "\n" ;

        ++caseNumber;
    }

    outFile.close();
}
