#ifndef TMTIMEMANAGER_H
#define TMTIMEMANAGER_H

#include <QObject>
#include <memory>
#include "TMlib/TMMapArea.h"

namespace TM {
class TMTimeManager : public QObject {
    Q_OBJECT
public:
    explicit TMTimeManager(QObject *parent = 0, double timestep = INT_MAX);

    double sendingTimeStep() const;

    void setSendingTimeStep(double sendingTimeStep);

    void setMaxTimeStep(double m_maxTimeStep) noexcept;

    double step() const noexcept;

public slots:
    void  updateSendingTimeStep(double const sendingTimeStep);
private:
    double m_timestep;
    double m_maxTimeStep;
    double m_sendingTimeStep;
};
}

#endif // TMTIMEMANAGER_H
