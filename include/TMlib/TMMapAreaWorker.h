#ifndef MAPAREAWORKER_H
#define MAPAREAWORKER_H

#include <iostream>
#include <memory>
#include "TMMapArea.h"

namespace TM{
namespace Map{
class MapAreaWorker
{
private:
    std::shared_ptr<MapArea <double>> m_eta;
    std::shared_ptr<MapArea <double>> m_etaOld;
    std::shared_ptr<MapArea <double>> m_max;
    std::shared_ptr<MapArea <double>> m_min;
    std::shared_ptr<MapArea <double>> m_bathymetry;

    std::shared_ptr<MapArea <double>> m_etaCurrent;
    std::shared_ptr<MapArea <double>> m_etaNext;
    std::shared_ptr<MapArea <double>> m_uCurrent;
    std::shared_ptr<MapArea <double>> m_uNext;
    std::shared_ptr<MapArea <double>> m_vCurrent;
    std::shared_ptr<MapArea <double>> m_vNext;

    std::string m_bathymetryPath;
    void readBathymetryFromFileDat();
public:
    MapAreaWorker() = default;
    bool readBathymetryFromFile();
    bool setBathymetryPath(const std::string& path, bool readFromFile = false);
    std::shared_ptr<MapArea <double>> bathymetry();
    std::shared_ptr<MapArea <double>> eta();
    std::shared_ptr<MapArea <double>> etaCurrent();
    std::shared_ptr<MapArea <double>> etaNext();
    std::shared_ptr<MapArea <double>> uCurrent();
    std::shared_ptr<MapArea <double>> uNext();
    std::shared_ptr<MapArea <double>> vCurrent();
    std::shared_ptr<MapArea <double>> vNext();
};
}
}
#endif // MAPAREAWORKER_H
