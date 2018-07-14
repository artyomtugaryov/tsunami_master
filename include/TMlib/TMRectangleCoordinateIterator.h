#ifndef TMMRECTANGLECOORDINATEITERATOR_H
#define TMMRECTANGLECOORDINATEITERATOR_H

#include "TMlib/TMCoordinateIterator.h"
#include "TMlib/TMRectangleMapArea.h"

#include <memory>

using namespace TM::Map;

namespace TM {
    namespace Map {

        template<typename DataType>
        class RectangleMapArea;

        template<typename DataType>
        class RectangleCoordinateIterator : public CoordinateIterator<DataType> {

        public:
            RectangleCoordinateIterator();

            explicit RectangleCoordinateIterator(const MapArea<DataType> *container = nullptr,
                                                 const std::size_t index = 0) {};


            virtual ~RectangleCoordinateIterator() {};

            bool operator==(const std::shared_ptr<CoordinateIterator<DataType>> &other) const override;

            bool operator!=(const std::shared_ptr<CoordinateIterator<DataType>> &other) const override;

            //typename TM::Map::RectangleCoordinateIterator<DataType>::reference operator*() const {};

            const std::shared_ptr<CoordinateIterator<DataType>> & operator++() override ;

            const std::shared_ptr<CoordinateIterator<DataType>> & operator--() override ;
        private:

            static inline const std::shared_ptr<RectangleCoordinateIterator<DataType>>& dynamic_ptr_cast(const std::shared_ptr<CoordinateIterator<DataType>> &ptr);

        private:
            std::shared_ptr<MapArea<DataType>> m_container;
            std::size_t m_index;
        };
    }
}


#endif //TMMRECTANGLECOORDINATEITERATOR_H
