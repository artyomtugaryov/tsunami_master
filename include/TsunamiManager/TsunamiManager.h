#ifndef TSUNAMIMANAGER_H
#define TSUNAMIMANAGER_H
#include <QObject>
#include "MapData.h"
#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMException.h>

namespace TsunamiManagerInfo {

class TsunamiManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(MapData *mapData READ mapData CONSTANT)

public:
    TsunamiManager(QObject *parent = nullptr);
    MapData * mapData() const;

public slots:
    void readBathymetryFromFile();
private:
    TsunamiManagerInfo::MapData* m_mapData;
    TM::Map::MapAreaWorker* m_mapAreaWorker;
};
}
#endif //TSUNAMIMANAGER_H
