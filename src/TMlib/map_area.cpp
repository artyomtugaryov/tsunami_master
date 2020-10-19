#include <algorithm>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <math.h>

#include "TMlib/map_area.h"
#include "TMlib/exception.h"
#include "TMlib/scheme.h"
#include "TMlib/scheme23.h"

using namespace TM;
using namespace TM::Map;
using namespace TM::Scheme;

using namespace std;

template<typename DataType>
MapArea<DataType>::MapArea(const size_t &sizeX, const size_t &sizeY, const DataType &defaultValue) : m_sizeX(sizeX),
                                                                                                     m_sizeY(sizeY),
                                                                                                     m_startX(0),
                                                                                                     m_startY(0),
                                                                                                     m_stepX(1),
                                                                                                     m_stepY(1),
                                                                                                     m_endX(sizeX - 1),
                                                                                                     m_endY(sizeX - 1),
                                                                                                     m_data(m_sizeX * m_sizeY, defaultValue) {}

template<typename DataType>
MapArea<DataType>::MapArea(const MapArea<DataType> &other) : m_sizeX(other.m_sizeX),
                                                             m_sizeY(other.m_sizeY),
                                                             m_startX(other.m_startX),
                                                             m_startY(other.m_startY),
                                                             m_stepX(other.m_stepX),
                                                             m_stepY(other.m_stepY),
                                                             m_endX(other.m_endX),
                                                             m_endY(other.m_endY) {
    this->m_data = other.m_data;
}


template<typename DataType>
template<typename T>
MapArea<DataType>::MapArea(const MapArea<T> &other) : m_sizeX(other.sizeX()),
                                                      m_sizeY(other.sizeY()),
                                                      m_data(m_sizeX * m_sizeY, static_cast<DataType>(0)),
                                                      m_startX(other.startX()),
                                                      m_startY(other.startY()),
                                                      m_stepX(other.stepX()),
                                                      m_stepY(other.stepY()),
                                                      m_endX(other.endX()),
                                                      m_endY(other.endY()) {}

template<typename DataType>
template<typename T>
MapArea<DataType> &MapArea<DataType>::operator=(const MapArea<T> &other) {
    m_sizeX = other.sizeX();
    m_sizeY = other.sizeY();
    m_startX = other.startX();
    m_startY = other.startY();
    m_endX = other.endX();
    m_endY = other.endY();
    m_data.resize(m_sizeX * m_sizeY, static_cast<DataType>(0));
    return (*this);
}

template<typename DataType>
MapArea<DataType> &MapArea<DataType>::operator=(const MapArea<DataType> &other) {
    m_sizeX = other.sizeX();
    m_sizeY = other.sizeY();
    m_startX = other.startX();
    m_startY = other.startY();
    m_endX = other.endX();
    m_endY = other.endY();
    m_data = other.m_data;
    return (*this);
}

template<typename DataType>
size_t MapArea<DataType>::getIndex(const size_t &x, const size_t &y) const {
    if (x >= m_sizeX || y >= m_sizeY) {
        THROW_TM_EXCEPTION << "Out of range in (" << x << ", " << y << ") " << __FUNCTION__;
    }
    return (x + y * m_sizeX);
}

template<typename DataType>
size_t MapArea<DataType>::getIndexByPoint(double lon, double lat) const {
    auto x = static_cast<size_t>(round((lon - m_startX) / m_stepX));
    size_t y = m_sizeY - 1 - static_cast<size_t>(round((lat - m_startY) / m_stepY));
    return getIndex(x, y);
}

template<typename DataType>
size_t MapArea<DataType>::getIndexXByPoint(double lon) const {
    return static_cast<size_t>(round((lon - m_startX) / m_stepX));
}

template<typename DataType>
size_t MapArea<DataType>::getIndexYByPoint(double lat) const {
    return m_sizeY - 1 - static_cast<size_t>(round((lat - m_startY) / m_stepY));
}

template<typename DataType>
const size_t &MapArea<DataType>::sizeX() const noexcept {
    return m_sizeX;
}

template<typename DataType>
const size_t &MapArea<DataType>::sizeY() const noexcept {
    return m_sizeY;
}

template<typename DataType>
const double &MapArea<DataType>::stepX() const noexcept {
    return m_stepX;
}

template<typename DataType>
double MapArea<DataType>::stepY() const noexcept {
    return m_stepY;
}

template<typename DataType>
double MapArea<DataType>::startX() const noexcept {
    return m_startX;
}

template<typename DataType>
double MapArea<DataType>::startY() const noexcept {
    return m_startY;
}

template<typename DataType>
double MapArea<DataType>::endX() const noexcept {
    return m_endX;
}

template<typename DataType>
double MapArea<DataType>::endY() const noexcept {
    return m_endY;
}

template<typename DataType>
const DataType MapArea<DataType>::getDataByIndex(const size_t &x, const size_t &y) const {
    return m_data[getIndex(x, y)];
}

template<typename DataType>
DataType MapArea<DataType>::getDataByPoint(double longitude, double latitude) const {
    return m_data[getIndexByPoint(longitude, latitude)];
}

template<typename DataType>
void MapArea<DataType>::setSizeX(size_t sizeX) {
    if (m_sizeX != sizeX) {
        m_data.resize(m_sizeX * m_sizeY);
        m_sizeX = sizeX;
    }
}

template<typename DataType>
void MapArea<DataType>::setSizeY(size_t sizeY) {
    if (m_sizeY != sizeY) {
        m_data.resize(m_sizeX * m_sizeY);
        m_sizeY = sizeY;
    }
}

template<typename DataType>
void MapArea<DataType>::setStepX(double stepX) {
    m_stepX = stepX;
}

template<typename DataType>
void MapArea<DataType>::setStepY(double stepY) {
    m_stepY = stepY;
}

template<typename DataType>
void MapArea<DataType>::setStartX(double startX) {
    m_startX = startX;
}

template<typename DataType>
void MapArea<DataType>::setStartY(double startY) {
    m_startY = startY;
}

template<typename DataType>
void MapArea<DataType>::setEndX(double endX) {
    m_endX = endX;
}

template<typename DataType>
void MapArea<DataType>::setEndY(double endY) {
    m_endY = endY;
}

template<typename DataType>
void MapArea<DataType>::setDataByIndex(const size_t &x, const size_t &y, const DataType &value) {
    m_data[getIndex(x, y)] = value;
}

template<typename DataType>
void MapArea<DataType>::setDataByPoint(double longitude, double latitude, DataType value) {
    m_data[getIndexByPoint(longitude, latitude)] = value;
}

template<typename DataType>
void MapArea<DataType>::saveAsTextFile(string path, int setprecision) const {
    fstream file;
    file.open(path.c_str(), fstream::out);
    for (size_t y = 0; y < m_sizeY; y++) {
        for (size_t x = 0; x < m_sizeX; x++) {
            file << fixed << std::setprecision(setprecision) << m_data[getIndex(x, y)] << " ";
            file << "\t";
        }
        file << endl;
    }
}

template<typename DataType>
const DataType MapArea<DataType>::getMinValue() const {
    return *min_element(this->m_data.begin(), this->m_data.end());
}

template<typename DataType>
const DataType MapArea<DataType>::getMaxValue() const {
    return *max_element(m_data.begin(), m_data.end());
}

template
class MapArea<double>;

template
class MapArea<float>;

template MapArea<float>::MapArea(const MapArea<double> &);

template
class MapArea<bool>;

template MapArea<bool>::MapArea(const MapArea<double> &);

template
class MapArea<int>;

template MapArea<int>::MapArea(const MapArea<double> &);

template
class MapArea<types_cells>;

template MapArea<types_cells>::MapArea(const MapArea<double> &);

template MapArea<types_cells> &MapArea<types_cells>::operator=(const MapArea<double> &other);