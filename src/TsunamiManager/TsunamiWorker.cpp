#include "TsunamiManager/TsunamiWorker.h"

#include <QDebug>

TsunamiWorker::TsunamiWorker(std::shared_ptr<TM::Map::MapAreaWorker> mapAreaWorker,
                             std::shared_ptr<TM::Scheme::TMScheme> scheme,
                             std::shared_ptr<TM::Focus::Focus> focus,
                             std::shared_ptr<TM::TMTimeManager> timemanager,
                             std::shared_ptr<TM::TMSignal> tmsignal,
                             QObject *parent) :
    QObject(parent),
    m_mapAreaWorker(mapAreaWorker),
    m_scheme(scheme),
    m_focus(focus),
    m_timemanager(timemanager),
    m_signal(tmsignal),
    m_readed(false),
    m_command(ThreadCommand::None),
    m_updateTime(1),
    m_calculationTime(25000),
    m_isobath(-5)
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
}

void TsunamiWorker::readBathymetryFromFile()
{
    m_readed = m_mapAreaWorker->setBathymetryPath(m_bathymetryPath.toStdString(), true);
    m_command = ThreadCommand::None;
    emit readedFinished();
    emit finished();
}

void TsunamiWorker::setIsobath(double isobath)
{
    m_isobath = isobath;
}

void TsunamiWorker::setCalculationTime(int calculationTime)
{
    m_calculationTime = calculationTime;
}

std::shared_ptr<TM::Scheme::TMScheme> TsunamiWorker::scheme() const
{
    return m_scheme;
}

std::shared_ptr<TM::Focus::Focus> TsunamiWorker::focus() const
{
    return m_focus;
}

void TsunamiWorker::setFocus(const std::shared_ptr<TM::Focus::Focus> &focus)
{
    m_focus.reset();
    m_focus = focus;
}

void TsunamiWorker::setScheme(const std::shared_ptr<TM::Scheme::TMScheme> &scheme)
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
    if(!m_focus) {
        return;
    }
    if(!m_mapAreaWorker) {
        return;
    }
    if (!m_scheme) {
        m_scheme = std::make_shared<TM::Scheme::TMScheme24>();
    }
    m_scheme->configure(m_mapAreaWorker, m_focus, m_isobath, m_timemanager, m_signal);
    m_scheme->calculation(m_mapAreaWorker, m_calculationTime);
}
//TODO: remove before implement calculation part
bool TsunamiWorker::readed() const
{
    return m_readed;
}
