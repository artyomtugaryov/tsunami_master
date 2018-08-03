#include <TMlib/TMMapArea.h>
#include <TMlib/TMMapAreaWorker.h>

using namespace TM;
using namespace TM::Map;

void fillMap(const std::shared_ptr<MapArea<double>> &map) {
    for (size_t i(0); i < map->sizeX(); i++) {
        for (size_t j(0); j < map->sizeY(); j++) {
               map->setDataByIndex(i, j, 2.4);
        }
    }
}

int main(int argc, char *argv[]) {
    std::shared_ptr<MapArea<double>> bath = std::make_shared<MapArea<double>>(15, 15);
    fillMap(bath);
    std::shared_ptr<MapAreaWorker> areaWorker;
    areaWorker->setBathymetry(*bath);
    return 0;
}