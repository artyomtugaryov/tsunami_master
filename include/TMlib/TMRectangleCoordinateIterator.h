#ifndef TMMRECTANGLECOORDINATEITERATOR_H
#define TMMRECTANGLECOORDINATEITERATOR_H

#include "TMlib/TMCoordinateIterator.h"
#include "TMlib/TMRectangleMapArea.h"

#include <memory>


namespace TM {
    namespace Map {
        template<typename DataType>
        class RectangleMapArea;

        template<typename DataType>
        class RectangleCoordinateIterator : public TM::Map::CoordinateIterator<DataType> {

            friend class RectangleMapArea<DataType>;

        public:
            RectangleCoordinateIterator();

            explicit RectangleCoordinateIterator(const TM::Map::MapArea<DataType> *container = nullptr,
                                                 const std::size_t index = 0) {};

            RectangleCoordinateIterator(const TM::Map::RectangleCoordinateIterator<DataType> &) {};

            virtual ~RectangleCoordinateIterator() {};

            bool operator==(const std::unique_ptr<CoordinateIterator<DataType>> &other) const {};

            bool operator!=(const std::unique_ptr<CoordinateIterator<DataType>> &other) const {};

            //typename TM::Map::RectangleCoordinateIterator<DataType>::reference operator*() const {};

            //TM::Map::RectangleCoordinateIterator<DataType> &operator++() {};

            //TM::Map::RectangleCoordinateIterator<DataType> &operator--() {};

        private:
            TM::Map::MapArea<DataType> *m_container;
            std::size_t m_index;
        };

    }
}


#endif //TMMRECTANGLECOORDINATEITERATOR_H
