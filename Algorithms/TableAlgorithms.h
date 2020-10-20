#pragma once

#include "../InputHandler/Data/PizzeriaData.h"



namespace Algorithms
{
    namespace TableAlgorithms
    {
        enum class CellType
        {
            Pizzeria,
            FedBlock,
            None
        };

        struct Data
        {
            CellType cellType;
            InputHandler::Data::PizzeriaData * pizzeriaData;
        };



        void f();
    }
}
