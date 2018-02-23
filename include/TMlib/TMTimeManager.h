#ifndef TMTIMEMANAGER_H
#define TMTIMEMANAGER_H

#include <QObject>
#include <memory>
#include "TMlib/TMMapArea.h"

namespace TM {
class TMTimeManager : public QObject {
    Q_OBJECT
public:
    explicit TMTimeManager(QObject *parent = 0, double timestep = 0);

    void emitSignal(std::shared_ptr<TM::Map::MapArea<double>> map);

    double sendingTimeStep() const;

    void setSendingTimeStep(double sendingTimeStep);

    void setMaxTimeStep(double m_maxTimeStep) const noexcept;

    double step() const noexcept;

signals:
    void signalUpdate(std::shared_ptr<TM::Map::MapArea<double>>);

public slots:
    void  updateSendingTimeStep(double const sendingTimeStep);
private:
    double m_timestep;
    double m_maxTimeStep;
    double m_sendingTimeStep;
};
}

#endif // TMTIMEMANAGER_H
