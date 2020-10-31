#pragma once

#include "../InputHandler/Data/CityData.h"
#include "../InputHandler/Data/PizzeriaData.h"

#include <string>



namespace OutputCreator
{
    namespace Utilities
    {
        void HandleAndWriteData( std::list< InputHandler::Data::CityData > const & data, std::string const & outputFilePath );
    }
}
