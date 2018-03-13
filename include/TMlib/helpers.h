#ifndef TSUNAMIMANAGER_HELPERS_H
#define TSUNAMIMANAGER_HELPERS_H


#include <TMlib/TMMapArea.h>
#include <TMlib/TMScheme.h>

template <typename DataType>
void saveMapAreaAsImage(const std::shared_ptr<TM::Map::MapArea<DataType>> &area,
                        const std::string &savePath,
                        const std::shared_ptr<const TM::Map::MapArea<double>> &bath=nullptr,
                        const bool &drawBat=false);


#endif //TSUNAMIMANAGER_HELPERS_H


