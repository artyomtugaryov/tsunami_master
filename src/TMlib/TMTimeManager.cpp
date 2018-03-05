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
    updateSendingTimeStep(sendingTimeStep);
}

void TM::TMTimeManager::updateSendingTimeStep(const double sendingTimeStep){
    m_sendingTimeStep = sendingTimeStep;
    if (sendingTimeStep <= m_timestep){
        m_timestep = sendingTimeStep;
        return;
    }
    m_timestep = m_maxTimeStep;
}

double TM::TMTimeManager::step() const noexcept {
    return m_timestep;
}

void TM::TMTimeManager::setMaxTimeStep(double maxTimeStep) noexcept {
    this->m_maxTimeStep = maxTimeStep;
    if (m_timestep == std::numeric_limits<double>::max()){
        m_timestep = this->m_maxTimeStep;
    }
}
