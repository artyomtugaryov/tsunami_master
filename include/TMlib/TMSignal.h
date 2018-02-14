#ifndef TMSIGNAL_H
#define TMSIGNAL_H

#include <QObject>
#include <memory>
#include "TMlib/TMMapArea.h"

namespace TM{
class TMSignal : public QObject {
    Q_OBJECT
public:
    TMSignal(QObject *parent = 0): m_updateSendingTimeStep(true), m_SendingTimeStep(0){};
    void emitSignal(std::shared_ptr<TM::Map::MapArea<double>> map){
        emit signalUpdate(map);
    }

    bool m_updateSendingTimeStep;
    double m_SendingTimeStep;
signals:
    void signalUpdate(std::shared_ptr<TM::Map::MapArea<double>>);

public slots:
    void  updateSendingTimeStep(double const sendingTimeStep){
        m_SendingTimeStep = sendingTimeStep;
        m_updateSendingTimeStep = true;
    };
};
}

#endif // TMSIGNAL_H
