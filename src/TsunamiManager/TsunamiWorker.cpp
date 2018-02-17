#include "TsunamiManager/TsunamiWorker.h"

#include <QDebug>

TsunamiWorker::TsunamiWorker(std::shared_ptr<TM::Map::MapAreaWorker> mapAreaWorker,
                             std::shared_ptr<TM::Scheme::TMScheme24> scheme,
                             std::shared_ptr<TM::TMFocus> focus,
                             std::shared_ptr<TM::TMSignal> signal,
                             QObject *parent) :
    QObject(parent),
    m_mapAreaWorker(mapAreaWorker),
    m_scheme(scheme),
    m_focus(focus),
    m_signal(signal),
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
    qDebug() << "Zhopa 1";
}

std::shared_ptr<TM::Scheme::TMScheme24> TsunamiWorker::scheme() const
{
    return m_scheme;
}

std::shared_ptr<TM::TMFocus> TsunamiWorker::focus() const
{
    return m_focus;
}

void TsunamiWorker::setFocus(const std::shared_ptr<TM::TMFocus> &focus)
{
    m_focus.reset();
    m_focus = focus;
}

void TsunamiWorker::setScheme(const std::shared_ptr<TM::Scheme::TMScheme24> &scheme)
{
    m_scheme.reset();
    m_scheme = scheme;
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
{
    qDebug() << "Zhopa 6";
    if(m_focus.get() == NULL) qDebug() << "Zhopa 6.01";
    if(m_mapAreaWorker.get() == NULL) qDebug() << "Zhopa 6.01";
    //std::shared_ptr<TM::TMFocus> focus = std::make_shared<TM::TMFocus>("double_brick_10mup.txt");
    //m_scheme->configure(m_area, focus, -5);
    //std::shared_ptr<TM::Map::MapAreaWorker> area = std::make_shared<TM::Map::MapAreaWorker>("work.dat");
    m_scheme->configure(m_mapAreaWorker, m_focus, -5);
    qDebug() << "Zhopa 7";
    //m_scheme->calculation(m_mapAreaWorker, m_signal, 10000000);
}
//TODO: remove before implement calculation part
bool TsunamiWorker::readed() const
{
    return m_readed;
}
