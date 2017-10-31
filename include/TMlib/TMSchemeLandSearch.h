#ifndef TMSCHEMELANDSEARCH_H
#define TMSCHEMELANDSEARCH_H

#include <iostream>
#include <memory>
#include "TMMapAreaWorkerGroundswell.h"
#include "TMMapArea.h"

namespace TM{
namespace Scheme{
class LandSearch
{
public:
    LandSearch() = default;
    std::shared_ptr<TM::Map::MapArea <bool>> getLandMap(std::shared_ptr<TM::Map::MapAreaWorkerGroundswell>);
};
}
}

#endif // TMSCHEMELANDSEARCH_H
