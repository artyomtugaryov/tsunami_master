#include "TMlib/TMTimeManager.h"

TM::TMTimeManager::TMTimeManager(QObject *parent, double timestep):
    QObject(parent),
    m_timestep(timestep),
    m_maxTimeStep(timestep)
{
}

double TM::TMTimeManager::sendingTimeStep() const
{
    return m_sendingTimeStep;
}

void TM::TMTimeManager::setSendingTimeStep(double sendingTimeStep)
{
    m_sendingTimeStep = sendingTimeStep;
}

void TM::TMTimeManager::updateSendingTimeStep(const double sendingTimeStep){
    m_sendingTimeStep = sendingTimeStep;
    if (sendingTimeStep <= m_timestep){
        m_timestep = sendingTimeStep;
        return;
    }
    if (sendingTimeStep > m_maxTimeStep){
        m_timestep = m_maxTimeStep;
    }
}

double TM::TMTimeManager::step() const noexcept {
    return m_timestep;
}

void TM::TMTimeManager::setMaxTimeStep(double m_maxTimeStep) const noexcept {
    m_maxTimeStep = m_maxTimeStep;
}
