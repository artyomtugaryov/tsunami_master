#ifndef MAPAREAWORKER_H
#define MAPAREAWORKER_H

#include <iostream>
#include <memory>
#include "MapArea.h"

namespace Map{

class MapAreaWorker
{
private:
    std::shared_ptr<MapArea> m_eta;
    std::shared_ptr<MapArea> m_etaOld;
    std::shared_ptr<MapArea> m_max;
    std::shared_ptr<MapArea> m_min;
    std::shared_ptr<MapArea> m_bathymetry;
    std::__cxx11::string m_bathymetryPath;
    void readBathymetryFromFileDat();
    void testDraw();
public:
    MapAreaWorker();
    void readBathymetryFromFile();
    void setBathymetryPath(std::__cxx11::string path, bool readFromFile = false);
};
}
#endif // MAPAREAWORKER_H
