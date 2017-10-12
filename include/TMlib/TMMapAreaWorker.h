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
    std::string m_bathymetryPath;
    void readBathymetryFromFileDat();
public:
    MapAreaWorker() = default;
    bool readBathymetryFromFile();
    bool setBathymetryPath(const std::string& path, bool readFromFile = false);
    std::shared_ptr<MapArea <double>> bathymetry();
};
}
}
#endif // MAPAREAWORKER_H
