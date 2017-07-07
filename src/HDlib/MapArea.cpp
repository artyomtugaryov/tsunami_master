#include "HDlib/MapArea.h"

#include <iostream>
#include <cstdio>
#include <fstream>

Map::MapArea::MapArea(int sizeX, int sizeY) :
    m_sizeX(sizeX), m_sizeY(sizeY)
{
    using namespace std;
    //m_data = shared_ptr <double>(new double (sizeX*sizeY), std::default_delete<double[]>());
   // m_data = make_shared <double>((sizeX*sizeY));
    m_data = std::make_shared<double> (new double[sizeX * sizeY]);
    for (int i = 0; i < sizeX * sizeY; i++) {
        std::cout << i <<  "   ||   ";
        m_data.get()[i] = 1;
        cout<< m_data.get()[i] << std::endl;
    }
}

Map::MapArea::MapArea()
{

}

int Map::MapArea::getIndex(int x, int y)
{
    return (x + y * m_sizeY);
}

int Map::MapArea::getIndexByPoint(double lat, double lon)
{
 //   return{ (int)((x - start_x) / delta_x), size_y - 1 - (int)(((y - start_y) / delta_y)) };
    int x = (int)((lat - m_startX) / m_stepX);
    int y = m_sizeY - 1 - (int)(((lon - m_startY) / m_stepY));
    return getIndex(x, y);   // **
}

int Map::MapArea::sizeX() const noexcept
{
    return m_sizeX;
}

int Map::MapArea::sizeY() const noexcept
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

double Map::MapArea::getDataByIndex(int x, int y)
{
    //return m_data.get().operator[](getIndex(x,y)];
    return m_data.get()[getIndex(x,y)];
}

double Map::MapArea::getDataByPoint(double latitude, double longitude)
{
    //double* data = (m_data.get() + getIndexByPoint(longitude, latitude));
    //if (data == NULL) {
    //    return 0.;
    //}
    int data = m_data.get()[getIndexByPoint(latitude, longitude)];
    std::cout << data << "\n";
    return m_data.get()[getIndexByPoint(latitude, longitude)];
}

void Map::MapArea::setSizeX(int sizeX)
{
    if (m_sizeX  != sizeX) {
        m_sizeX = sizeX;
    }
}

void Map::MapArea::setSizeY(int sizeY)
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

void Map::MapArea::setDataByIndex(int x, int y, double value)
{
    double data = getDataByIndex(x, y);
    if (data != value) {
        //m_data[getIndex(x,y)] = value;
       m_data.get()[getIndex(x,y)] = value;
    }
}

void Map::MapArea::setDataByPoint(double latitude, double longitude, double value)
{
    double data = getDataByPoint(latitude, longitude);
    if (data != value) {
        //m_data[getIndexByPoint(longitude, latitude)] = value;
        m_data.get()[getIndexByPoint( latitude, longitude)] = value;
    }
}

void Map::MapArea::saveMapAreaToTextFile(std::__cxx11::string path)
{
    path = "";
    for (int i = 0; i < m_sizeX; i++) {
        for (int j = 0; j < m_sizeY; j++) {

        }
    }
}

void Map::MapArea::saveMapAreaToBinFile(std::__cxx11::string path)
{
    path = "";
    for (int i = 0; i < m_sizeX; i++) {
        for (int j = 0; j < m_sizeY; j++) {

        }
    }
}
