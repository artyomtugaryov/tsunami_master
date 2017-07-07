#ifndef MAPAREAWORKER_H
#define MAPAREAWORKER_H

#include <iostream>
#include <memory>
#include "MapArea.h"

namespace Map{

class MapAreaWorker
{
private:
    MapArea* m_eta;
    MapArea* m_etaOld;
    MapArea* m_max;
    MapArea* m_min;
    MapArea* m_bathymetry;
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
