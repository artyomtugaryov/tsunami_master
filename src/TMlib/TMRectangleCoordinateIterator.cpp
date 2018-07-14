#include "TMlib/TMRectangleCoordinateIterator.h"

template<typename DataType>
TM::Map::RectangleCoordinateIterator<DataType>::RectangleCoordinateIterator():m_index(0), m_container(nullptr){}


template<typename DataType>
bool TM::Map::RectangleCoordinateIterator<DataType>::operator==(const std::shared_ptr<CoordinateIterator<DataType>> &other_ptr) const{
    auto other = RectangleCoordinateIterator<DataType>::dynamic_ptr_cast(other_ptr);
    return (m_index ==  other->m_index) && (m_container == other->m_container);
}

template<typename DataType>
bool TM::Map::RectangleCoordinateIterator<DataType>::operator!=(const std::shared_ptr<CoordinateIterator<DataType>> &other_ptr) const{
    auto other = RectangleCoordinateIterator<DataType>::dynamic_ptr_cast(other_ptr);
    return (m_index !=  other->m_index) || (m_container != other->m_container);
}

template<typename DataType>
const std::shared_ptr<CoordinateIterator<DataType>> & TM::Map::RectangleCoordinateIterator<DataType>::operator++(){
    m_index++;
    return std::make_shared<CoordinateIterator<DataType>>(this);
}

template<typename DataType>
const std::shared_ptr<CoordinateIterator<DataType>> & TM::Map::RectangleCoordinateIterator<DataType>::operator--(){
    m_index--;
    return std::make_shared<CoordinateIterator<DataType>>(this);
}


template<typename DataType>
const std::shared_ptr<RectangleCoordinateIterator<DataType>>& TM::Map::RectangleCoordinateIterator<DataType>::dynamic_ptr_cast(const std::shared_ptr<CoordinateIterator<DataType>> &ptr){
    return dynamic_cast<const std::shared_ptr<RectangleCoordinateIterator<DataType>>&>(*ptr);
}
