#ifndef TMMAPAREAWORKERGROUNDSWELL_H
#define TMMAPAREAWORKERGROUNDSWELL_H

#include <iostream>
#include <memory>
#include "TMMapAreaWorker.h"

namespace TM{
namespace Map{
class MapAreaWorkerGroundswell : public MapAreaWorker
{
private:
    std::shared_ptr<MapArea <double>> m_H;
    std::shared_ptr<MapArea <double>> m_uu;
    std::shared_ptr<MapArea <double>> m_vv;
public:
    void init(std::shared_ptr<MapAreaWorker>);
    MapAreaWorkerGroundswell() = default;
    std::shared_ptr<MapArea <double>> H();
    std::shared_ptr<MapArea <double>> uu();
    std::shared_ptr<MapArea <double>> vv();
};
}
}
#endif // TMMAPAREAWORKERGROUNDSWELL_H
