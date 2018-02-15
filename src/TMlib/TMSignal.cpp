#include "TMlib/TMSignal.h"

TM::TMSignal::TMSignal(QObject *parent, double sendingTimeStep):
    QObject(parent),
    m_updateSendingTimeStep(true),
    m_sendingTimeStep(sendingTimeStep)
{
}

void TM::TMSignal::emitSignal(std::shared_ptr<TM::Map::MapArea<double> > map)
{
    emit signalUpdate(map);
}

double TM::TMSignal::TMSignal::sendingTimeStep() const
{
    return m_sendingTimeStep;
}

void TM::TMSignal::TMSignal::setSendingTimeStep(double sendingTimeStep)
{
    m_sendingTimeStep = sendingTimeStep;
}

void TM::TMSignal::TMSignal::setUpdateSendingTimeStep(bool updateSendingTimeStep)
{
    m_updateSendingTimeStep = updateSendingTimeStep;
}

bool TM::TMSignal::updateSendingTimeStep() const
{
    return m_updateSendingTimeStep;
}

void TM::TMSignal::updateSendingTimeStep(const double sendingTimeStep){
    m_sendingTimeStep = sendingTimeStep;
    m_updateSendingTimeStep = true;
}
