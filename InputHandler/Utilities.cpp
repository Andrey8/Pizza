#include "Utilities.h"

#include <fstream>
#include <exception>
#include <sstream>



std::list< InputHandler::Data::CityData > InputHandler::Utilities::ReadData( const std::string & inputFilePath )
{
    //using triple = std::array< int, 3 >;

    std::ifstream inFile;
    inFile.open( inputFilePath );

    if ( !inFile.is_open() )
    {
        throw std::runtime_error( "File has not opened." );
    }

    std::list< Data::CityData > result;

    int width = 0;
    int height = 0;
    int k = 0;

    std::list< Data::PizzeriaData > pizzerias;
    std::string line;
    bool firstTestCaseLine = true;
    int testCaseLineNumber = 0;
    while ( std::getline( inFile, line ) )
    {
        if ( firstTestCaseLine )
        {
            std::istringstream iss( line );
            iss >> width >> height >> k;

            testCaseLineNumber = k;
            firstTestCaseLine = false;
        }
        else
        {
            if ( testCaseLineNumber == 0 )
            {
                result.push_back( Data::CityData( width, height, pizzerias ) );

                pizzerias.clear();

                std::istringstream iss( line );
                iss >> width >> height >> k;

                testCaseLineNumber = k;
                firstTestCaseLine = false;

                continue;
            }

            if ( line == "0" )
            {
                break;
            }

            std::istringstream iss( line );
            int x = 0;
            int y = 0;
            int c = 0;
            iss >> x >> y >> c;

            pizzerias.push_back( { x, y, c } );
            --testCaseLineNumber;
        }
    }

    inFile.close();

    return result;
}
