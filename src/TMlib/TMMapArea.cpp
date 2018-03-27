#include "TMlib/TMMapArea.h"
#include "TMlib/TMException.h"
#include "TMlib/TMScheme.h"
#include <algorithm>
#include <fstream>
#include <iomanip>

template<typename DataType>
TM::Map::MapArea<DataType>::MapArea(std::size_t sizeX, std::size_t sizeY, DataType defaultValue) :
        m_sizeX(sizeX), m_sizeY(sizeY), m_data(m_sizeX * m_sizeY, defaultValue) {
}


template<typename DataType>
template <typename T> TM::Map::MapArea<DataType>::MapArea(const std::shared_ptr<const MapArea<T>> &other) :
        m_sizeX(other->sizeX()),
        m_sizeY(other->sizeY()),
        m_data(m_sizeX * m_sizeY, static_cast<DataType>(0)),
        m_startX(other->startX()),
        m_startY(other->startY()),
        m_endX(other->endX()),
        m_endY(other->endY()) {
    setStepX((m_endX - m_startX) / (m_sizeX - 1));
    setStepY((m_endY - m_startY) / (m_sizeY - 1));
}


template<typename DataType>
std::size_t TM::Map::MapArea<DataType>::getIndex(const std::size_t &x, const std::size_t &y) const {
    if (x >= m_sizeX || y >= m_sizeY) {
        THROW_TM_EXCEPTION << "Out of range in (" << x << ", " << y << ") " << __FUNCTION__;
    }
    return (x + y * m_sizeX);
}

template<typename DataType>
std::size_t TM::Map::MapArea<DataType>::getIndexByPoint(double lon, double lat) const {
    std::size_t x = static_cast<std::size_t>(std::round((lon - m_startX) / m_stepX));
    std::size_t y = m_sizeY - 1 - static_cast<std::size_t>(std::round((lat - m_startY) / m_stepY));
    return getIndex(x, y);
}

template<typename DataType>
std::size_t TM::Map::MapArea<DataType>::getIndexXByPoint(double lon) const
{
    return static_cast<std::size_t>(std::round((lon - m_startX) / m_stepX));
}

template<typename DataType>
std::size_t TM::Map::MapArea<DataType>::getIndexYByPoint(double lat) const
{
    return m_sizeY - 1 - static_cast<std::size_t>(std::round((lat - m_startY) / m_stepY));
}

template<typename DataType>
std::size_t TM::Map::MapArea<DataType>::sizeX() const noexcept {
    return m_sizeX;
}

template<typename DataType>
std::size_t TM::Map::MapArea<DataType>::sizeY() const noexcept {
    return m_sizeY;
}

template<typename DataType>
double TM::Map::MapArea<DataType>::stepX() const noexcept {
    return m_stepX;
}

template<typename DataType>
double TM::Map::MapArea<DataType>::stepY() const noexcept {
    return m_stepY;
}

template<typename DataType>
double TM::Map::MapArea<DataType>::startX() const noexcept {
    return m_startX;
}

template<typename DataType>
double TM::Map::MapArea<DataType>::startY() const noexcept {
    return m_startY;
}

template<typename DataType>
double TM::Map::MapArea<DataType>::endX() const noexcept {
    return m_endX;
}

template<typename DataType>
double TM::Map::MapArea<DataType>::endY() const noexcept {
    return m_endY;
}

template<typename DataType>
DataType TM::Map::MapArea<DataType>::getDataByIndex(const std::size_t &x, const std::size_t &y) const {
    return m_data[getIndex(x, y)];
}

template<typename DataType>
DataType TM::Map::MapArea<DataType>::getDataByPoint(double longitude, double latitude) const {
    return m_data[getIndexByPoint(longitude, latitude)];
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setSizeX(std::size_t sizeX) {
    if (m_sizeX != sizeX) {
        m_sizeX = sizeX;
    }
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setSizeY(std::size_t sizeY) {
    if (m_sizeY != sizeY) {
        m_sizeY = sizeY;
    }
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setStepX(double stepX) {
    m_stepX = stepX;
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setStepY(double stepY) {
    m_stepY = stepY;
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setStartX(double startX) {
    m_startX = startX;
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setStartY(double startY) {
    m_startY = startY;
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setEndX(double endX) {
    m_endX = endX;
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setEndY(double endY) {
    m_endY = endY;
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setDataByIndex(std::size_t &x, std::size_t &y, DataType value) {
    m_data[getIndex(x, y)] = value;
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setDataByPoint(double longitude, double latitude, DataType value) {
    m_data[getIndexByPoint(longitude, latitude)] = value;
}

template<typename DataType>
void TM::Map::MapArea<DataType>::saveAsTextFile(std::string path, int setprecision) const {
    //TODO: Will need check rounding for different data types.
    std::fstream file;
    file.open(path.c_str(), std::fstream::out);
    //TODO: Remove after resolve problem with brick
//    double max = *std::max_element(m_data.begin(), m_data.end());
//    double min = *std::min_element(m_data.begin(), m_data.end());
    //END TODO
    for (std::size_t y = 0; y < m_sizeY; y++) {
        for (std::size_t x = 0; x < m_sizeX; x++) {
            file << std::fixed << std::setprecision(setprecision) << m_data[getIndex(x, y)] << " ";
            file << "\t";
//
            //TODO: Remove after resolve problem with brick

            //END TODO
        }
        file << std::endl;
    }
    //TODO: Remove after resolve problem with brick
//    std::cout <<  max <<"\t"<<min<< std::endl;
    //END TODO
}

template<typename DataType>
void TM::Map::MapArea<DataType>::saveMapAreaToBinFile(std::string path) {
    path = "";
    for (std::size_t i = 0; i < m_sizeX; i++) {
        for (std::size_t j = 0; j < m_sizeY; j++) {

        }
    }
}

template<typename DataType>
const DataType TM::Map::MapArea<DataType>::getMinValue() const {
    return *std::min_element(this->m_data.begin(), this->m_data.end());
}

template<typename DataType>
DataType TM::Map::MapArea<DataType>::min(){
    return *std::min_element(m_data.begin(), m_data.end());
}

template<typename DataType>
DataType TM::Map::MapArea<DataType>::max(){
    return *std::max_element(m_data.begin(), m_data.end());
}
template<typename DataType>
DataType const& operator[](int index) const;
{
    return state[index];
}
template class TM::Map::MapArea<double>;
template TM::Map::MapArea<double>::MapArea(const std::shared_ptr<const TM::Map::MapArea<double>> &);

template class TM::Map::MapArea<float>;
template TM::Map::MapArea<float>::MapArea(const std::shared_ptr<const TM::Map::MapArea<double>> &);

template class TM::Map::MapArea<bool>;
template TM::Map::MapArea<bool>::MapArea(const std::shared_ptr<const TM::Map::MapArea<double>> &);

template class TM::Map::MapArea<int>;
template TM::Map::MapArea<int>::MapArea(const std::shared_ptr<const TM::Map::MapArea<double>> &);

template class TM::Map::MapArea<TM::Scheme::types_cells>;
template TM::Map::MapArea<TM::Scheme::types_cells>::MapArea(const std::shared_ptr<const TM::Map::MapArea<double>> &);
