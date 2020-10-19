#include <TMlib/map_area.h>
#include <TMlib/map_area_worker.h>
#include <TMlib/scheme23.h>

using namespace TM;
using namespace TM::Map;
using namespace TM::Scheme;

void fillMap(MapArea<double> &map) {
    for (size_t i(0); i < map.sizeX(); i++) {
        for (size_t j(0); j < map.sizeY(); j++) {
               map.setDataByIndex(i, j, -12.4);
        }
    }
}

int main(int argc, char *argv[]) {
    MapArea<double> bath(15, 15);
    MapAreaWorker areaWorker;
    Scheme23 scheme;

    fillMap(bath);

    areaWorker.setBathymetry(bath);
    areaWorker.conigure(-5);

    scheme.configure(areaWorker);

    scheme.calculation(areaWorker, 1);
    return 0;
}