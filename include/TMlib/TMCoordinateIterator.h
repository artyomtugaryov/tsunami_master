#ifndef TMMAPAREAITERATOR_H
#define TMMAPAREAITERATOR_H

#include <memory>

namespace TM {
    namespace Map {

        template<typename DataType>
        class CoordinateIterator: public std::iterator<std::forward_iterator_tag, DataType> {

        public:
            virtual ~CoordinateIterator() {};

            virtual bool operator==(const std::shared_ptr<CoordinateIterator<DataType>> &other) const = 0;

            virtual bool operator!=(const std::shared_ptr<CoordinateIterator<DataType>> &other) const = 0;

            //virtual typename CoordinateIterator<DataType>::reference operator*() const = 0;

            virtual const std::shared_ptr<CoordinateIterator<DataType>> & operator++() = 0;

            virtual const std::shared_ptr<CoordinateIterator<DataType>> & operator--() = 0;
        private:


        };
    }
}


#endif //TMMAPAREAITERATOR_H
