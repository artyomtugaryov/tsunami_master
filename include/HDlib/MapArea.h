#ifndef MAPAREA_H
#define MAPAREA_H

#include <iostream>
#include <memory>
#include <vector>

namespace Map{
struct Index {
    std::size_t x, y;
};
template <typename DataType>
class MapArea
{
private:
    std::size_t m_sizeX;
    std::size_t m_sizeY;
    double m_startX;
    double m_startY;
    double m_stepX;
    double m_stepY;
    double m_endX;
    double m_endY;
    std::vector<DataType> m_data;
    std::size_t getIndex(std::size_t x, std::size_t y) const;
    std::size_t getIndexByPoint(double lat, double lon) const;

public:
    MapArea(std::size_t sizeX, std::size_t sizeY);
    MapArea();
    std::size_t sizeX() const noexcept;
    std::size_t sizeY() const noexcept;
    double stepX() const noexcept;
    double stepY() const noexcept;
    double startX() const noexcept;
    double startY() const noexcept;
    double endX() const noexcept;
    double endY() const noexcept;
    DataType getDataByIndex(std::size_t x, std::size_t y) const;
    DataType getDataByPoint(double latitude, double longitude) const;
    void setSizeX(std::size_t sizeX);
    void setSizeY(std::size_t sizeY);
    void setStepX(double stepX);
    void setStepY(double stepY);
    void setStartX(double startX);
    void setStartY(double startY);
    void setEndX(double endX);
    void setEndY(double endY);
    void setDataByIndex(std::size_t x, std::size_t y, DataType value);
    void setDataByPoint(double latitude, double longitude, DataType value);
    void saveMapAreaToTextFile(std::__cxx11::string path, int setprecision);
    void saveMapAreaToBinFile(std::__cxx11::string path);
};
}
#endif // MAPAREA_H
