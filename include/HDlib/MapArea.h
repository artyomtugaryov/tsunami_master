#ifndef MAPAREA_H
#define MAPAREA_H

#include <iostream>
#include <memory>

namespace Map{
struct Index {
    int x, y;
};
class MapArea
{
private:
    int m_sizeX;
    int m_sizeY;
    double m_startX;
    double m_startY;
    double m_stepX;
    double m_stepY;
    double m_endX;
    double m_endY;
    std::shared_ptr<double> m_data;
    int getIndex(int x, int y);
    int getIndexByPoint(double lat, double lon);

public:
    MapArea(int sizeX, int sizeY);
    MapArea();
    int sizeX() const noexcept;
    int sizeY() const noexcept;
    double stepX() const noexcept;
    double stepY() const noexcept;
    double startX() const noexcept;
    double startY() const noexcept;
    double endX() const noexcept;
    double endY() const noexcept;
    double getDataByIndex(int x, int y);
    double getDataByPoint(double latitude, double longitude);
    void setSizeX(int sizeX);
    void setSizeY(int sizeY);
    void setStepX(double stepX);
    void setStepY(double stepY);
    void setStartX(double startX);
    void setStartY(double startY);
    void setEndX(double endX);
    void setEndY(double endY);
    void setDataByIndex(int x, int y, double value);
    void setDataByPoint(double latitude, double longitude, double value);
    void saveMapAreaToTextFile(std::__cxx11::string path);
    void saveMapAreaToBinFile(std::__cxx11::string path);
};
}
#endif // MAPAREA_H
