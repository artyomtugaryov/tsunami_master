#include "HDlib/MapArea.h"

#include <iostream>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <stdexcept>

template <typename DataType>
Map::MapArea<DataType>::MapArea(std::size_t sizeX, std::size_t sizeY) :
    m_sizeX(sizeX), m_sizeY(sizeY), m_data(m_sizeX * m_sizeY, 1)
{
}

template <typename DataType>
Map::MapArea<DataType>::MapArea()
{
}

template <typename DataType>
std::size_t Map::MapArea<DataType>::getIndex(std::size_t x, std::size_t y) const
{
    // TODO: Will be check by Artem
    if(x >= m_sizeX || y >= m_sizeY) {
        throw std::out_of_range("Out of range");
    }
    return (x + y * m_sizeX);
}

template <typename DataType>
std::size_t Map::MapArea<DataType>::getIndexByPoint(double lat, double lon) const
{
    std::size_t x = static_cast<std::size_t>(((lat - m_startX) / m_stepX));
    std::size_t y = m_sizeY - 1 - static_cast<std::size_t>(((lon - m_startY) / m_stepY));
    return getIndex(x, y);
}

template <typename DataType>
std::size_t Map::MapArea<DataType>::sizeX() const noexcept
{
    return m_sizeX;
}

template <typename DataType>
std::size_t Map::MapArea<DataType>::sizeY() const noexcept
{
    return m_sizeY;
}

template <typename DataType>
double Map::MapArea<DataType>::stepX() const noexcept
{
    return m_stepX;
}

template <typename DataType>
double Map::MapArea<DataType>::stepY() const noexcept
{
    return m_stepY;
}

template <typename DataType>
double Map::MapArea<DataType>::startX() const noexcept
{
    return m_startX;
}

template <typename DataType>
double Map::MapArea<DataType>::startY() const noexcept
{
    return m_startY;
}

template <typename DataType>
double Map::MapArea<DataType>::endX() const noexcept
{
    return m_endX;
}

template <typename DataType>
double Map::MapArea<DataType>::endY() const noexcept
{
    return m_endY;
}

template <typename DataType>
DataType Map::MapArea<DataType>::getDataByIndex(std::size_t x, std::size_t y) const
{
    return m_data[getIndex(x,y)];
}

template <typename DataType>
DataType Map::MapArea<DataType>::getDataByPoint(double latitude, double longitude) const
{
    return m_data[getIndexByPoint(latitude, longitude)];
}

template <typename DataType>
void Map::MapArea<DataType>::setSizeX(std::size_t sizeX)
{
    if (m_sizeX  != sizeX) {
        m_sizeX = sizeX;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::setSizeY(std::size_t sizeY)
{
    if (m_sizeY  != sizeY) {
        m_sizeY = sizeY;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::setStepX(double stepX)
{
    if (m_stepX  != stepX) {
        m_stepX = stepX;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::setStepY(double stepY)
{
    if (m_stepY  != stepY) {
        m_stepY = stepY;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::setStartX(double startX)
{
    if (m_startX  != startX) {
        m_startX = startX;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::setStartY(double startY)
{
    if (m_startY != startY) {
        m_startY = startY;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::setEndX(double endX)
{
    if (m_endX != endX) {
        m_endX = endX;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::setEndY(double endY)
{
    if (m_endY != endY) {
        m_endY = endY;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::setDataByIndex(std::size_t x, std::size_t y, DataType value)
{
    double data = getDataByIndex(x, y);
    if (data != value) {
       m_data[getIndex(x,y)] = value;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::setDataByPoint(double latitude, double longitude, DataType value)
{
    DataType data = getDataByPoint(latitude, longitude);
    if (data != value) {
        m_data[getIndexByPoint(latitude, longitude)] = value;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::saveMapAreaToTextFile(std::__cxx11::string path, int setprecision)
{
    //TODO: Will need check rounding for different data types.
    std::fstream file;
    file.open(path.c_str(), std::fstream::out);

    for(std::size_t y = 0; y < m_sizeY; y++){
        for(std::size_t x = 0; x < m_sizeX; x++){
            file << std::fixed << std::setprecision(setprecision) << m_data[getIndex(x,y)] << " ";
            file << "\t";
        }
        file << std::endl;
    }
}

template <typename DataType>
void Map::MapArea<DataType>::saveMapAreaToBinFile(std::__cxx11::string path)
{
    path = "";
    for (std::size_t i = 0; i < m_sizeX; i++) {
        for (std::size_t j = 0; j < m_sizeY; j++) {

        }
    }
}

template class Map::MapArea<double>;
template class Map::MapArea<float>;
template class Map::MapArea<bool>;
template class Map::MapArea<int>;
