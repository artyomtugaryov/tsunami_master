#include "TMlib/TMMapAreaWorkerGroundswell.h"
#include <TMlib/TMException.h>

std::shared_ptr<TM::Map::MapArea <double> > TM::Map::MapAreaWorkerGroundswell::HCurrent()
{
    return m_HCurrent;
}

std::shared_ptr<TM::Map::MapArea <double> > TM::Map::MapAreaWorkerGroundswell::HPrevious()
{
    return m_HPrevious;
}

std::shared_ptr<TM::Map::MapArea <double> > TM::Map::MapAreaWorkerGroundswell::uu()
{
    return m_uu;
}

std::shared_ptr<TM::Map::MapArea <double> > TM::Map::MapAreaWorkerGroundswell::vv()
{
    return m_vv;
}
