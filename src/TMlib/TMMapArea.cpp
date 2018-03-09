#include "TMlib/TMMapArea.h"
#include "TMlib/TMException.h"
#include "TMlib/TMScheme.h"
#include <algorithm>
#include <fstream>
#include <iomanip>

//TODO: For test. Remove after all work with calculation part.
#include <QImage>
#include <PlotLib/Plot2d.h>
#include <PlotLib/ColorMap.h>
namespace {
const int Width = 300;
const int Height = 20;
}
//TODO END

template<typename DataType>
TM::Map::MapArea<DataType>::MapArea(std::size_t sizeX, std::size_t sizeY, DataType defaultValue) :
        m_sizeX(sizeX), m_sizeY(sizeY), m_data(m_sizeX * m_sizeY, defaultValue) {
}


template<typename DataType>
std::size_t TM::Map::MapArea<DataType>::getIndex(const std::size_t &x, const std::size_t &y) const {
    if (x >= m_sizeX || y >= m_sizeY) {
        THROW_TM_EXCEPTION << "Out of range in ("<<x<<", "<<y<<") " << __FUNCTION__;
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
void TM::Map::MapArea<DataType>::setDataByIndex(std::size_t& x, std::size_t& y, DataType value) {
    m_data[getIndex(x, y)] = value;
}

template<typename DataType>
void TM::Map::MapArea<DataType>::setDataByPoint(double longitude, double latitude, DataType value) {
    m_data[getIndexByPoint(longitude, latitude)] = value;
}

template<typename DataType>
void TM::Map::MapArea<DataType>::saveMapAreaToTextFile(std::string path, int setprecision) const {
    //TODO: Will need check rounding for different data types.
//    std::fstream file;
//    file.open(path.c_str(), std::fstream::out);
    //TODO: Remove after resolve problem with brick
    double max = *std::max_element(m_data.begin(), m_data.end());
    double min = *std::min_element(m_data.begin(), m_data.end());
    //END TODO
//    for (std::size_t y = 0; y < m_sizeY; y++) {
//        for (std::size_t x = 0; x < m_sizeX; x++) {
//            file << std::fixed << std::setprecision(setprecision) << m_data[getIndex(x, y)] << " ";
//            file << "\t"

//            //TODO: Remove after resolve problem with brick
//
//            //END TODO
//        }
//        file << std::endl;
//    }
    //TODO: Remove after resolve problem with brick
    std::cout <<  max <<"\t"<<min<< std::endl;
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

//TODO: For test. Remove after all work with calculation part.
template<typename DataType>
void TM::Map::MapArea<DataType>::savePlotMapArea(std::__cxx11::string savePath,
                                           const std::shared_ptr<const TM::Map::MapArea<double> > bath)
{

    QImage* plotImage = new QImage(bath->sizeX() + Width, bath->sizeY() + Height, QImage::Format_RGB32);
    PlotLib::Plot2d plot;
    plot.setImage(plotImage);
    plot.setRegion(QRectF( QPointF(bath->startX() + bath->stepX() / 2.,
                          bath->startY() + stepY() / 2.),
                  QPointF(bath->endX() - bath->stepX() / 2.,
                          bath->endY() - bath->stepY() / 2.)));
    plot.setWindow(QRect(0, 0, bath->sizeX() + 300, bath->sizeY() + 20));

    PlotLib::ColorMap colorMap({{0, QColor(0, 91, 65)},
                       {200, QColor(201, 180, 102)},
                       {800, QColor(160, 55, 0)},
                       {1500, QColor(121, 83, 83)},
                       {6000, QColor(214, 214, 214)}});

    PlotLib::ColorMap etaColorBarMap({{-3, QColor(38, 0, 255)},
                                      {-0.1, QColor(222, 255, 248)},
                                      {0, QColor(222, 255, 248)},
                                      {1, QColor(128, 0, 128)},
                                      {3, QColor(255, 0, 0)},
                                      {5, QColor(255, 128, 0)},
                                      {8, QColor(255, 255, 0)},
                                      {11, QColor(0, 255, 0 )}});

    colorFunc2D f = [&colorMap, &bath, &etaColorBarMap, this](double x, double y)->QColor {
        QColor c;
        double data = bath->getDataByPoint(x, y);
        if (data > 0.0) {
            c = colorMap.getColor(data);
        }
        else
        {
            c = etaColorBarMap.getColor(getDataByPoint(x, y));
        }
        return c;
    };
    std::cout << "Point 1\n";
    plot.plotColorFunction(f);
    std::cout << "Point 2\n";
    plot.setAxisX(true);
    plot.setAxisY(true);
    plot.setAxisLabelY("N");
    plot.setAxisLabelX("E");
    plot.drawAxis(28);
    plot.drawGrid(false, 28, 1, 0, 2, 0);
    std::cout << "Point 3\n";
    std::vector<double> ticks;
    for(int i = etaColorBarMap.min(); i < etaColorBarMap.max(); i++) {
        ticks.push_back(i);
    }
    std::cout << "Point 4\n";
    plot.drawColorbar(etaColorBarMap, ticks, 22);
    std::cout << "Point 5\n";
    plotImage->save(QString::fromStdString(savePath), "PNG");
    std::cout << "Point 6\n";
    delete plotImage;
    std::cout << "Point 7\n";
    return;
    std::cout << "Point 8\n";
}
//TODO END

template
class TM::Map::MapArea<double>;

template
class TM::Map::MapArea<float>;

template
class TM::Map::MapArea<bool>;

template
class TM::Map::MapArea<int>;

template
class TM::Map::MapArea<TM::Scheme::types_cells>;
