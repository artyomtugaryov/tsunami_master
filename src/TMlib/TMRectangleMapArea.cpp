#include "TMlib/TMRectangleMapArea.h"
#include "TMlib/TMException.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <memory>


template<typename DataType>
TM::Map::RectangleMapArea<DataType>::RectangleMapArea(std::size_t sizeX, std::size_t sizeY, DataType defaultValue):
        m_sizeX(sizeX), m_sizeY(sizeY),
        m_startX(0), m_startY(0),
        m_endX(sizeX - 1), m_endY(sizeX - 1),
        m_data(m_sizeX * m_sizeY, defaultValue) {
    m_stepX = calcStepByCoordinate(m_startX, m_endX, sizeX);
    m_stepY = calcStepByCoordinate(m_startY, m_endY, sizeY);
}

template<typename DataType>
template<typename OtherDataType>
TM::Map::RectangleMapArea<DataType>::RectangleMapArea(
        const std::shared_ptr<const RectangleMapArea<OtherDataType>> &other)
        : m_sizeX(other->sizeLongitude()), m_sizeY(other->sizeLatitude()),
          m_startX(other->minLongitude()), m_startY(other->minLatitude()),
          m_data(m_sizeX * m_sizeY, static_cast<DataType>(0)),
          m_endX(other->maxLongitude()), m_endY(other->maxLatitude()) {
    m_stepX = calcStepByCoordinate(other->minLongitude(), other->maxLongitude(), other->sizeLongitude());
    m_stepY = calcStepByCoordinate(other->minLatitude(), other->maxLatitude(), other->sizeLatitude());
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::minLongitude() const noexcept {
    return m_startX;
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::minLatitude() const noexcept {
    return m_startY;
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::maxLongitude() const noexcept {
    return m_endX;
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::maxLatitude() const noexcept {
    return m_endY;
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::stepLongitude() const noexcept {
    return m_stepX;
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::stepLatitude() const noexcept {
    return m_stepY;
}

template<typename DataType>
std::size_t TM::Map::RectangleMapArea<DataType>::sizeLongitude() const noexcept {
    return m_sizeX;
}

template<typename DataType>
std::size_t TM::Map::RectangleMapArea<DataType>::sizeLatitude() const noexcept {
    return m_sizeY;
}

template<typename DataType>
std::size_t TM::Map::RectangleMapArea<DataType>::getIndex(const std::size_t &x, const std::size_t &y) const {
    if (x >= m_sizeX || y >= m_sizeY) {
        THROW_TM_EXCEPTION << "Out of range in (" << x << ", " << y << ") " << __FUNCTION__;
    }
    return (x + y * m_sizeX);
}

template<typename DataType>
std::size_t TM::Map::RectangleMapArea<DataType>::getIndexXByPoint(double lon) const {
    return static_cast<std::size_t>(std::round((lon - m_startX) / m_stepX));
}

template<typename DataType>
std::size_t TM::Map::RectangleMapArea<DataType>::getIndexByPoint(double lon, double lat) const {
    auto x = static_cast<std::size_t>(std::round((lon - m_startX) / m_stepX));
    std::size_t y = m_sizeY - static_cast<std::size_t>(std::round((lat - m_startY) / m_stepY)) - 1;
    return getIndex(x, y);
}

template<typename DataType>
std::size_t TM::Map::RectangleMapArea<DataType>::getIndexYByPoint(double lat) const {
    return m_sizeY - static_cast<std::size_t>(std::round((lat - m_startY) / m_stepY)) - 1;
}


template<typename DataType>
DataType TM::Map::RectangleMapArea<DataType>::getDataByIndex(const std::size_t &x, const std::size_t &y) const {
    return m_data[getIndex(x, y)];
}

template<typename DataType>
DataType TM::Map::RectangleMapArea<DataType>::getDataByPoint(const double &longitude, const double &latitude) const {
    return m_data[getIndexByPoint(longitude, latitude)];
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setSizeLongitude(const std::size_t &sizeX) {
    if (m_sizeX != sizeX) {
        m_data.resize(m_sizeX * m_sizeY);
        m_sizeX = sizeX;
        m_stepX = calcStepByCoordinate(m_startX, m_endX, m_sizeX);
    }
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setSizeLatitude(const std::size_t &sizeY) {
    if (m_sizeY != sizeY) {
        m_data.resize(m_sizeX * m_sizeY);
        m_sizeY = sizeY;
        m_stepY = calcStepByCoordinate(m_startY, m_endY, m_sizeY);
    }
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setMinLongitude(double startX) {
    m_startX = startX;
    m_stepX = calcStepByCoordinate(m_startX, m_endX, m_sizeX);
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setMintLatitude(double startY) {
    m_startY = startY;
    m_stepY = calcStepByCoordinate(m_startY, m_endY, m_sizeY);

}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setMaxLongitude(double endX) {
    m_endX = endX;
    m_stepX = calcStepByCoordinate(m_startX, m_endX, m_sizeX);

}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setMaxLatitude(double endY) {
    m_endY = endY;
    m_stepY = calcStepByCoordinate(m_startY, m_endY, m_sizeY);

}

template<typename DataType>
void
TM::Map::RectangleMapArea<DataType>::setDataByIndex(const std::size_t &x, const std::size_t &y, const DataType &value) {
    m_data[getIndex(x, y)] = value;
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setDataByPoint(const double &longitude, const double &latitude,
                                                         const DataType &value) {
    m_data[getIndexByPoint(longitude, latitude)] = value;
}

template<typename DataType>
const DataType TM::Map::RectangleMapArea<DataType>::getMinValue() const {
    return *std::min_element(this->m_data.begin(), this->m_data.end());
}

template<typename DataType>
const DataType TM::Map::RectangleMapArea<DataType>::getMaxValue() const {
    return *std::max_element(m_data.begin(), m_data.end());
}

template<typename DataType>
double
TM::Map::RectangleMapArea<DataType>::calcStepByCoordinate(const double &minCoordinate, const double &maxCoordinate,
                                                          const std::size_t &size) const {
    return (maxCoordinate - minCoordinate) / (size - 1);
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::saveAsTextFile(std::string path, int setprecision) const {
    std::fstream file;
    file.open(path.c_str(), std::fstream::out);
    for (std::size_t y = 0; y < m_sizeY; y++) {
        for (std::size_t x = 0; x < m_sizeX; x++) {
            file << static_cast<double>(m_data[getIndex(x, y)]) << " ";
            file << "\t";
        }
        file << std::endl;
    }
}

template<typename DataType>
TM::Map::MapArea<DataType>::ptr_iterator TM::Map::RectangleMapArea<DataType>::beginLongitude(){
    return std::make_unique<TM::Map::MapArea<DataType>::iterator>(this, 0);
}


template
class TM::Map::RectangleMapArea<double>;

template
TM::Map::RectangleMapArea<double>::RectangleMapArea(const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &);

template
class TM::Map::RectangleMapArea<float>;

template
TM::Map::RectangleMapArea<float>::RectangleMapArea(const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &);

template
class TM::Map::RectangleMapArea<bool>;

template
TM::Map::RectangleMapArea<bool>::RectangleMapArea(const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &);

template
class TM::Map::RectangleMapArea<int>;

template
TM::Map::RectangleMapArea<int>::RectangleMapArea(const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &);

template
class TM::Map::RectangleMapArea<TM::Map::TypesCells>;

template TM::Map::RectangleMapArea<TM::Map::TypesCells>::RectangleMapArea(
        const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &);