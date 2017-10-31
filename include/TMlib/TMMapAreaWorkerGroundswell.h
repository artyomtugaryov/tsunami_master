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
    std::shared_ptr<MapArea <double>> m_HCurrent;
    std::shared_ptr<MapArea <double>> m_HPrevious;
    std::shared_ptr<MapArea <double>> m_uu;
    std::shared_ptr<MapArea <double>> m_vv;
public:
    MapAreaWorkerGroundswell() = default;
    std::shared_ptr<MapArea <double>> HCurrent();
    std::shared_ptr<MapArea <double>> HPrevious();
    std::shared_ptr<MapArea <double>> uu();
    std::shared_ptr<MapArea <double>> vv();
};
}
}
#endif // TMMAPAREAWORKERGROUNDSWELL_H
