#include "TsunamiManager/TsunamiWorker.h"

#include <QDebug>

TsunamiWorker::TsunamiWorker(std::shared_ptr<TM::Map::MapAreaWorker> mapAreaWorker, QObject *parent) :
    QObject(parent),
    m_mapAreaWorker(mapAreaWorker),
    m_readed(false),
    m_command(ThreadCommand::None),
    m_updateTime(1)
{

}

void TsunamiWorker::execute()
{
    switch (m_command) {
    case ThreadCommand::ReadBathymetry:
        readBathymetryFromFile();
        break;
    case ThreadCommand::RunCalculation:
        runCalculation();
        break;
    case ThreadCommand::None:
    default:
        emit finished();
        break;
    }
}

QString TsunamiWorker::bathymetryPath() const
{
    return m_bathymetryPath;
}

void TsunamiWorker::setBathymetryPath(const QString &path)
{
    if (m_bathymetryPath == path) {
        return;
    }
    m_bathymetryPath = path;
    qDebug() << path;
}

void TsunamiWorker::readBathymetryFromFile()
{
    m_readed = m_mapAreaWorker->setBathymetryPath(m_bathymetryPath.toStdString(), true);
    m_command = ThreadCommand::None;
    emit readedFinished();
    emit finished();
}

void TsunamiWorker::setMapAreaWorker(const std::shared_ptr<TM::Map::MapAreaWorker> &mapAreaWorker)
{
    m_mapAreaWorker.reset();
    m_mapAreaWorker = mapAreaWorker;
}

void TsunamiWorker::setCommand(const ThreadCommand &command)
{
    m_command = command;
}

//TODO: remove before implement calculation part
void TsunamiWorker::runCalculation()
{}
//TODO: remove before implement calculation part
bool TsunamiWorker::readed() const
{
    return m_readed;
}
