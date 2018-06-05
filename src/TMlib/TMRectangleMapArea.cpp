#include "TMlib/TMRectangleMapArea.h"
#include "TMlib/TMException.h"
#include <algorithm>
#include <fstream>
#include <iomanip>

template<typename DataType>
TM::Map::RectangleMapArea<DataType>::RectangleMapArea(): m_sizeX(0), m_sizeY(0),
                                                         m_startX(0), m_startY(0),
                                                         m_stepX(0), m_stepY(0),
                                                         m_endX(0), m_endY(0),
                                                         m_data(0, static_cast<DataType>(0)) {}

template<typename DataType>
TM::Map::RectangleMapArea<DataType>::RectangleMapArea(std::size_t sizeX, std::size_t sizeY, DataType defaultValue):
        m_sizeX(sizeX), m_sizeY(sizeY),
        m_startX(0), m_startY(0),
        m_stepX(1), m_stepY(1),
        m_endX(sizeX - 1), m_endY(sizeX - 1),
        m_data(m_sizeX * m_sizeY, defaultValue) {}

template<typename DataType>
template<typename T>
TM::Map::RectangleMapArea<DataType>::RectangleMapArea(const std::shared_ptr<const RectangleMapArea<T>> &other)
        : m_sizeX(other->sizeLongitude()), m_sizeY(other->sizeLatitude()),
          m_startX(other->startLongitude()), m_startY(other->startLatitude()),
          m_stepX((other->endLongitude() - other->startLongitude()) / (other->sizeLongitude()- 1)),
          m_stepY((other->endLatitude() - other->startLatitude()) / (other->sizeLatitude()- 1)),
          m_data(m_sizeX * m_sizeY, static_cast<DataType>(0)),
          m_endX(other->endLongitude()), m_endY(other->endLatitude())
{}

template<typename DataType>
std::size_t TM::Map::RectangleMapArea<DataType>::getIndex(const std::size_t &x, const std::size_t &y) const {
    if (x >= m_sizeX || y >= m_sizeY) {
        THROW_TM_EXCEPTION << "Out of range in (" << x << ", " << y << ") " << __FUNCTION__;
    }
    return (x + y * m_sizeX);
}

template<typename DataType>
std::size_t TM::Map::RectangleMapArea<DataType>::getIndexByPoint(double lon, double lat) const {
    auto x = static_cast<std::size_t>(std::round((lon - m_startX) / m_stepX));
    std::size_t y = m_sizeY - 1 - static_cast<std::size_t>(std::round((lat - m_startY) / m_stepY));
    return getIndex(x, y);
}

template<typename DataType>
std::size_t TM::Map::RectangleMapArea<DataType>::getIndexXByPoint(double lon) const {
    return static_cast<std::size_t>(std::round((lon - m_startX) / m_stepX));
}

template<typename DataType>
std::size_t TM::Map::RectangleMapArea<DataType>::getIndexYByPoint(double lat) const {
    return m_sizeY - 1 - static_cast<std::size_t>(std::round((lat - m_startY) / m_stepY));
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
double TM::Map::RectangleMapArea<DataType>::stepLongitude() const noexcept {
    return m_stepX;
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::stepLatitude() const noexcept {
    return m_stepY;
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::startLongitude() const noexcept {
    return m_startX;
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::startLatitude() const noexcept {
    return m_startY;
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::endLongitude() const noexcept {
    return m_endX;
}

template<typename DataType>
double TM::Map::RectangleMapArea<DataType>::endLatitude() const noexcept {
    return m_endY;
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
void TM::Map::RectangleMapArea<DataType>::setSizeLongitude(std::size_t sizeX) {
    if (m_sizeX != sizeX) {
        m_data.resize(m_sizeX * m_sizeY);
        m_sizeX = sizeX;
    }
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setSizeLatitude(std::size_t sizeY) {
    if (m_sizeY != sizeY) {
        m_data.resize(m_sizeX * m_sizeY);
        m_sizeY = sizeY;
    }
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setStepLongitude(double stepX) {
    m_stepX = stepX;
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setStepLatitude(double stepY) {
    m_stepY = stepY;
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setStartLongitude(double startX) {
    m_startX = startX;
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setStartLatitude(double startY) {
    m_startY = startY;
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setEndLongitude(double endX) {
    m_endX = endX;
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setEndLatitude(double endY) {
    m_endY = endY;
}

template<typename DataType>
void
TM::Map::RectangleMapArea<DataType>::setDataByIndex(const std::size_t &x, const std::size_t &y, const DataType &value) {
    m_data[getIndex(x, y)] = value;
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::setDataByPoint(const double &longitude, const double &latitude, const DataType &value) {
    m_data[getIndexByPoint(longitude, latitude)] = value;
}

template<typename DataType>
void TM::Map::RectangleMapArea<DataType>::saveAsTextFile(std::string path, int setprecision) const {
    std::fstream file;
    file.open(path.c_str(), std::fstream::out);
    for (std::size_t y = 0; y < m_sizeY; y++) {
        for (std::size_t x = 0; x < m_sizeX; x++) {
            file << std::fixed << std::setprecision(setprecision) << m_data[getIndex(x, y)] << " ";
            file << "\t";
        }
        file << std::endl;
    }
}

template<typename DataType>
const DataType TM::Map::RectangleMapArea<DataType>::getMinValue() const {
    return *std::min_element(this->m_data.begin(), this->m_data.end());
}

template<typename DataType>
const DataType TM::Map::RectangleMapArea<DataType>::getMaxValue() const {
    return *std::max_element(m_data.begin(), m_data.end());
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