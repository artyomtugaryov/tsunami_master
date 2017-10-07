#include "TsunamiManager/TsunamiManager.h"
#include <QDebug>
TsunamiManagerInfo::TsunamiManager::TsunamiManager(QObject *parent) :
    QObject(parent),
    m_mapData(new TsunamiManagerInfo::MapData(this)),
    m_mapAreaWorker(new TM::Map::MapAreaWorker)
{
    //m_mapAreaWorker->setBathymetryPath("work.dat");
}

TsunamiManagerInfo::MapData *TsunamiManagerInfo::TsunamiManager::mapData() const
{
    return m_mapData;
}

QString TsunamiManagerInfo::TsunamiManager::path() const
{
    return m_path;
}

void TsunamiManagerInfo::TsunamiManager::readBathymetryFromFile()
{
    m_mapAreaWorker->setBathymetryPath(m_path.toStdString(), true);
}

void TsunamiManagerInfo::TsunamiManager::setPath(QString path)
{
    if (m_path == path)
        return;

    m_path = path.remove("file:///");

    qDebug() << path;
    emit pathChanged();
}
