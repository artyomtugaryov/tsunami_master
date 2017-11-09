#include "TMlib/TMMapAreaWorkerGroundswell.h"
#include <TMlib/TMException.h>

void TM::Map::MapAreaWorkerGroundswell::init(std::shared_ptr<TM::Map::MapAreaWorker> map)
{

}

std::shared_ptr<TM::Map::MapArea <double> > TM::Map::MapAreaWorkerGroundswell::H()
{
    return m_H;
}

std::shared_ptr<TM::Map::MapArea <double> > TM::Map::MapAreaWorkerGroundswell::uu()
{
    return m_uu;
}

std::shared_ptr<TM::Map::MapArea <double> > TM::Map::MapAreaWorkerGroundswell::vv()
{
    return m_vv;
}
