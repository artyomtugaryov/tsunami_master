#ifndef TMMAPAREA_H
#define TMMAPAREA_H

#include "TMlib/TMCoordinateIterator.h"

#include <vector>
#include <memory>


namespace TM {
    namespace Map {
        /**
         * @enum TypesCells
         * @brief Describes types of map's cells
         */
        enum class TypesCells : unsigned {
            LAND = 0,
            WATER = 1,
            BOUNDARY1 = 2,  //water near land
            BOUNDARY2 = 3   //water end of grid
        };

        template<typename DataType>
        class MapArea {
        public:
            MapArea() = default;

            virtual ~MapArea() = default;

            virtual const DataType getMinValue() const = 0;

            virtual const DataType getMaxValue() const = 0;

            /*
             * Iterators and function return iterators
             */

            using iterator=TM::Map::CoordinateIterator<DataType>;

            using ptr_iterator=std::unique_ptr<iterator>;

            virtual ptr_iterator beginLatitude() = 0; // Y

            /*virtual ptr_iterator beginLongitude() = 0; // X

            virtual ptr_iterator endLongitude() = 0;// X

            virtual ptr_iterator endLatitude() = 0; // Y*/
        };
    }
}


#endif // TMMAPAREA_H
