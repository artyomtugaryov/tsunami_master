#ifndef TSUNAMIMANAGER_HELPERS_H
#define TSUNAMIMANAGER_HELPERS_H


#include <TMlib/TMRectangleMapArea.h>

template <typename DataType>
void saveMapAreaAsImage(const std::shared_ptr<TM::Map::RectangleMapArea<DataType>> &area,
                        const std::string &savePath,
                        const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &bath=nullptr);


#endif //TSUNAMIMANAGER_HELPERS_H


