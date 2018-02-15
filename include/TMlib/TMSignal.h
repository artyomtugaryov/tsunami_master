#ifndef TMSIGNAL_H
#define TMSIGNAL_H

#include <QObject>
#include <memory>
#include "TMlib/TMMapArea.h"

namespace TM {
class TMSignal : public QObject {
    Q_OBJECT
public:
    explicit TMSignal(QObject *parent = 0, double sendingTimeStep = 0);

    void emitSignal(std::shared_ptr<TM::Map::MapArea<double>> map);

    double sendingTimeStep() const;
    bool updateSendingTimeStep() const;

    void setSendingTimeStep(double sendingTimeStep);
    void setUpdateSendingTimeStep(bool updateSendingTimeStep);

signals:
    void signalUpdate(std::shared_ptr<TM::Map::MapArea<double>>);

public slots:
    void  updateSendingTimeStep(double const sendingTimeStep);
private:
    bool m_updateSendingTimeStep;
    double m_sendingTimeStep;
};
}

#endif // TMSIGNAL_H
