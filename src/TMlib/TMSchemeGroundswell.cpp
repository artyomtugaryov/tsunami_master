#include "TMlib/TMSchemeGroundswell.h"
#include "TMlib/TMSchemeLandSearch.h"
#include <TMlib/TMException.h>

double TM::Scheme::Groundswell::stepT() {
    return m_stepT;
}

void TM::Scheme::Groundswell::setStepT(double t) {
    m_stepT = t;
}

double TM::Scheme::Groundswell::timeStepsCount() {
    return m_timeStepsCount;
}

void TM::Scheme::Groundswell::setTimeStepsCount(int count) {
    m_timeStepsCount = count;
}

void TM::Scheme::Groundswell::calculation(std::shared_ptr<TM::Map::MapAreaWorker>
                                          afterMainCalculation) {

    std::shared_ptr<TM::Map::MapAreaWorkerGroundswell> map;

    //int K = afterMainCalculation->bathymetry()->sizeX();
    //int L = afterMainCalculation->bathymetry()->sizeY();

    double t = 0.0;

    for (int i = 0; i < afterMainCalculation->bathymetry()->sizeX(); i++)
        for (int j = 0; j < afterMainCalculation->bathymetry()->sizeY(); j++)
            map->HPrevious()->setDataByIndex(i, j, afterMainCalculation->etaCurrent()->getDataByIndex(i, j););

    // Perform main calculations (Sielecki scheme)
    for (int n = 0; n < timeStepsCount(); n++)
    {
        // Set the bottom slope
        for (int i = 0; i < afterMainCalculation->bathymetry()->sizeX(); i++)
            for (int j = 0; j < afterMainCalculation->bathymetry()->sizeY(); j++)
                map->HCurrent()->setDataByIndex(i, j, map->HPrevious()->getDataByIndex(i, j));

        // Evaluate the surface of water h(x, y, (n+1)*dt) (height of every
        // point) at next moment by known values of height h(x, y, n*t) and
        // horizontal velocities u(x, y, n*dt) and v(x, y, n*dt) of every
        // point at the previos moment.
        std::shared_ptr<MapArea <bool>> landFlags = TM::Scheme::LandSearch::getLandMap(map);

        t += stepT();
    }
}
