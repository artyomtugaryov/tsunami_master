#include "HDlib/MapArea.h"

#include <iostream>
#include <cstdio>
#include <fstream>

Map::MapArea::MapArea(std::size_t sizeX, std::size_t sizeY) :
    m_sizeX(sizeX), m_sizeY(sizeY)
{
    using namespace std;
    m_data.resize(m_sizeX * m_sizeY, 1);
    for (std::size_t i=0; i < m_sizeX * m_sizeY; i++) {
        std::cout << i << "  ||  ";
        cout<< m_data[i] << std::endl;
    }
}

Map::MapArea::MapArea()
{

}

std::size_t Map::MapArea::getIndex(std::size_t x, std::size_t y) const
{
    // TODO: if x>m_sizeX && x>m_sizeY
    return (x + y * m_sizeY);
}

std::size_t Map::MapArea::getIndexByPoint(double lat, double lon) const
{
 //   return{ (int)((x - start_x) / delta_x), size_y - 1 - (int)(((y - start_y) / delta_y)) };
    std::size_t x = static_cast<int>((lat - m_startX) / m_stepX);
    std::size_t y = m_sizeY - 1 - static_cast<int>(((lon - m_startY) / m_stepY));
    return getIndex(x, y);   // **
}

std::size_t Map::MapArea::sizeX() const noexcept
{
    return m_sizeX;
}

std::size_t Map::MapArea::sizeY() const noexcept
{
    return m_sizeY;
}

double Map::MapArea::stepX() const noexcept
{
    return m_stepX;
}

double Map::MapArea::stepY() const noexcept
{
    return m_stepY;
}

double Map::MapArea::startX() const noexcept
{
    return m_startX;
}

double Map::MapArea::startY() const noexcept
{
    return m_startY;
}

double Map::MapArea::endX() const noexcept
{
    return m_endX;
}

double Map::MapArea::endY() const noexcept
{
    return m_endY;
}

double Map::MapArea::getDataByIndex(std::size_t x, std::size_t y) const
{
    //return m_data.get().operator[](getIndex(x,y)];
    return m_data[getIndex(x,y)];
}

double Map::MapArea::getDataByPoint(double latitude, double longitude) const
{
    //double* data = (m_data.get() + getIndexByPoint(longitude, latitude));
    //if (data == NULL) {
    //    return 0.;
    //}
    std::size_t data = m_data[getIndexByPoint(latitude, longitude)];
    std::cout << data << "\n";
    return m_data[getIndexByPoint(latitude, longitude)];
}

void Map::MapArea::setSizeX(std::size_t sizeX)
{
    if (m_sizeX  != sizeX) {
        m_sizeX = sizeX;
    }
}

void Map::MapArea::setSizeY(std::size_t sizeY)
{
    if (m_sizeY  != sizeY) {
        m_sizeY = sizeY;
    }
}

void Map::MapArea::setStepX(double stepX)
{
    if (m_stepX  != stepX) {
        m_stepX = stepX;
    }
}

void Map::MapArea::setStepY(double stepY)
{
    if (m_stepY  != stepY) {
        m_stepY = stepY;
    }
}

void Map::MapArea::setStartX(double startX)
{
    if (m_startX  != startX) {
        m_startX = startX;
    }
}

void Map::MapArea::setStartY(double startY)
{
    if (m_startY != startY) {
        m_startY = startY;
    }
}

void Map::MapArea::setEndX(double endX)
{
    if (m_endX != endX) {
        m_endX = endX;
    }
}

void Map::MapArea::setEndY(double endY)
{
    if (m_endY != endY) {
        m_endY = endY;
    }
}

void Map::MapArea::setDataByIndex(std::size_t x, std::size_t y, double value)
{
    double data = getDataByIndex(x, y);
    if (data != value) {
        //m_data[getIndex(x,y)] = value;
       m_data[getIndex(x,y)] = value;
    }
}

void Map::MapArea::setDataByPoint(double latitude, double longitude, double value)
{
    double data = getDataByPoint(latitude, longitude);
    if (data != value) {
        //m_data[getIndexByPoint(longitude, latitude)] = value;
        m_data[getIndexByPoint( latitude, longitude)] = value;
    }
}

void Map::MapArea::saveMapAreaToTextFile(std::__cxx11::string path)
{
    path = "";
    for (std::size_t i = 0; i < m_sizeX; i++) {
        for (std::size_t j = 0; j < m_sizeY; j++) {

        }
    }
}

void Map::MapArea::saveMapAreaToBinFile(std::__cxx11::string path)
{
    path = "";
    for (std::size_t i = 0; i < m_sizeX; i++) {
        for (std::size_t j = 0; j < m_sizeY; j++) {

        }
    }
}
