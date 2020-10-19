#pragma once

#include <list>
#include <exception>



namespace InputHandler
{
    namespace Data
    {
        class CityData
        {
        public:
            CityData( int width, int height, std::list< PizzeriaData > const & data )
                : m_width( width ),
                  m_height( height ),
                  m_data( data )
            {
                if ( !CheckData( width, height, data ) )
                {
                    throw std::exception();
                }
            }

            int GetWidth() const { return m_width; }
            int GetHeight() const { return m_height; }
            std::list< PizzeriaData > const & GetPizzeriasData() const { return m_data; }
        private:
            int m_width;
            int m_height;
            std::list< PizzeriaData > m_data;

            bool CheckData( int cityWidth, int cityHeight, std::list< PizzeriaData > const & data )
            {
                int capacitiesSum = 0;
                for ( PizzeriaData const & pd : data )
                {
                    capacitiesSum += pd.capacity;
                }

                return capacitiesSum + data.size() == cityWidth * cityHeight;
            }
        };

    }
}
