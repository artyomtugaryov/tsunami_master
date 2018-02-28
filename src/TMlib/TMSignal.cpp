#include<TMSignal.h>

void TM::TMSignal::emitSignal(std::shared_ptr<TM::Map::MapArea<double> > map)
{
    emit signalUpdate(map);
}
