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
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
public:
    TsunamiManager(QObject *parent = nullptr);

    MapData * mapData() const;

    QString path() const;
    void setPath(QString path);

public slots:
    void readBathymetryFromFile();


signals:
    void pathChanged();

private:
    TsunamiManagerInfo::MapData* m_mapData;
    TM::Map::MapAreaWorker* m_mapAreaWorker;
    QString m_path;
};
}
#endif //TSUNAMIMANAGER_H
