#include "TsunamiManager/TsunamiManager.h"

TsunamiManagerInfo::TsunamiManager::TsunamiManager(QObject *parent) :
    QObject(parent),
    m_mapData(new TsunamiManagerInfo::MapData(this)),
    m_mapAreaWorker(new TM::Map::MapAreaWorker)
{
   m_mapAreaWorker->setBathymetryPath("work.dat");
}

TsunamiManagerInfo::MapData *TsunamiManagerInfo::TsunamiManager::mapData() const
{
    return m_mapData;
}

void TsunamiManagerInfo::TsunamiManager::readBathymetryFromFile()
{
    m_mapAreaWorker->readBathymetryFromFile();
}
