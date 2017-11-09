#include "TMlib/TMSchemeGroundswell.h"
#include "TMlib/TMSchemeLandSearch.h"
#include "TMlib/TMMapArea.h"
#include <TMlib/TMException.h>

double TM::Scheme::Groundswell::stepT() {
    return m_stepT;
}

void TM::Scheme::Groundswell::setStepT(double t) {
    m_stepT = t;
}

int TM::Scheme::Groundswell::timeStepsCount() {
    return m_timeStepsCount;
}

void TM::Scheme::Groundswell::setTimeStepsCount(int count) {
    m_timeStepsCount = count;
}

void TM::Scheme::Groundswell::calculation(std::shared_ptr<TM::Map::MapAreaWorker>
                                          afterMainCalculation) {

    int X = afterMainCalculation->bathymetry()->sizeX();
    int Y = afterMainCalculation->bathymetry()->sizeY();

    double t = 0.0;

    std::shared_ptr<TM::Map::MapAreaWorkerGroundswell> current;
    std::shared_ptr<TM::Map::MapAreaWorkerGroundswell> next;
    std::shared_ptr<TM::Scheme::LandSearch> landSearch;

    current->init(afterMainCalculation);

    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
        {
            current->H()->setDataByIndex(i, j, afterMainCalculation->eta()->getDataByIndex(i, j));
        }

    // Perform main calculations (Sielecki scheme)
    for (int n = 0; n < timeStepsCount(); n++)
    {
        // Set the bottom slope
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                next->H()->setDataByIndex(i, j, current->H()->getDataByIndex(i, j));

        // Evaluate the surface of water h(x, y, (n+1)*dt) (height of every
        // point) at next moment by known values of height h(x, y, n*t) and
        // horizontal velocities u(x, y, n*dt) and v(x, y, n*dt) of every
        // point at the previos moment.
        std::shared_ptr<TM::Map::MapArea <bool>> landFlags = landSearch->getLandMap(current);

        t += stepT();
    }
}
