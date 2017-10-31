#ifndef TMSCHEMEGROUNDSWELL_H
#define TMSCHEMEGROUNDSWELL_H

#include <memory>
#include <iostream>
#include "TMMapAreaWorkerGroundswell.h"

namespace TM{
namespace Scheme{
class Groundswell
{
private:
    double m_stepT; //шаг по времени
    int m_timeStepsCount;
public:
    Groundswell() = default;
    void setStepT(double t);
    double stepT();
    void setTimeStepsCount(int count);
    int timeStepsCount();
    virtual void calculation(std::shared_ptr<TM::Map::MapAreaWorker>);
};
}
}

#endif // TMSCHEMEGROUNDSWELL_H
