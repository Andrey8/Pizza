#pragma once

#include "Data/PizzeriaData.h"
#include "Data/CityData.h"

#include <list>
#include <string>



namespace InputHandler
{
    namespace Utilities
    {
        std::list< Data::CityData > ReadData( std::string const & inputFilePath );

    }
}
