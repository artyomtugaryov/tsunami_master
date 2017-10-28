#ifndef TMSCHEMEGROUNDSWELL_H
#define TMSCHEMEGROUNDSWELL_H

#include <memory>
#include <iostream>
#include "TMMapAreaWorker.h"

namespace TM{
namespace Scheme{
class Groundswell
{
private:
    //std::shared_ptr<TMMapAreaWorker> m_areaWorker;
    double m_stepT; //шаг по времени
public:
    Groundswell() = default;
    void setStepT(double t);
    double getStepT();
    virtual void calculation(std::shared_ptr<TM::Map::MapAreaWorker>);
};
}
}

#endif // TMSCHEMEGROUNDSWELL_H
