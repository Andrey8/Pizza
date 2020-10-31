#include "../InputHandler/Utilities.h"
#include "../InputHandler/Data/PizzeriaData.h"
#include "../InputHandler/Data/CityData.h"
#include "../OutputCreator/Utils.h"

#include <iostream>
#include <list>
#include <exception>



void PrintInfo()
{
    std::list< InputHandler::Data::CityData > const data = InputHandler::Utilities::ReadData( "input.txt" );

    for ( InputHandler::Data::CityData const & tc : data )
    {
        std::cout << "- TEST CASE info\n\n" ;
        std::cout << "City Width : " << tc.GetWidth() << std::endl;
        std::cout << "City Height : " << tc.GetHeight() << std::endl;
        std::cout << "Pizzerias Count : " << tc.GetPizzeriasData().size() << "\n\n" ;

        for ( InputHandler::Data::PizzeriaData const & data : tc.GetPizzeriasData() )
        {
            std::cout << "x : " << data.x << std::endl ;
            std::cout << "y : " << data.y << std::endl ;
            std::cout << "capacity : " << data.capacity << "\n\n" ;
        }

        std::cout << "\n\n\n" ;
    }
}



int main()
{
    try
    {
        //PrintInfo();

        std::list< InputHandler::Data::CityData > const data = InputHandler::Utilities::ReadData( "input.txt" );
        OutputCreator::Utilities::HandleAndWriteData( data, "result.txt" );
    }
    catch ( std::exception const & exc )
    {
        std::cout << exc.what() ;
    }
}
