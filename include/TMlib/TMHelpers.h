#ifndef TSUNAMIMANAGER_HELPERS_H
#define TSUNAMIMANAGER_HELPERS_H


#include <TMlib/TMMapArea.h>
#include <TMlib/TMScheme.h>

template<typename DataType>
void saveMapAreaAsImage(const MapArea<DataType> &area,
                        const std::string &savePath,
                        const MapArea<double> &bath = nullptr);


#endif //TSUNAMIMANAGER_HELPERS_H


