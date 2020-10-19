#ifndef TSUNAMIWORKER_H
#define TSUNAMIWORKER_H

#include <TMlib/map_area_worker.h>
#include <TMlib/exception.h>
#include <TMlib/scheme23.h>
#include <TMlib/focus.h>

#include <QObject>
#include <QSharedPointer>
#include <QString>

class TsunamiWorker : public QObject {
Q_OBJECT
    Q_ENUMS(ThreadCommand)
public:
    enum ThreadCommand {
        None = 0,
        ReadBathymetry,
        RunCalculation
    };

    explicit TsunamiWorker(std::shared_ptr<TM::Map::MapAreaWorker> mapAreaWorker,
                           std::shared_ptr<TM::Scheme::Scheme> scheme,
                           std::shared_ptr<TM::Focus::Focus> focus,
                           QObject *parent = 0);

    QString bathymetryPath() const;

    void setBathymetryPath(const QString &path);

    bool readed() const;

    void setCommand(const ThreadCommand &command);

    void runCalculation();

    void setMapAreaWorker(const std::shared_ptr<TM::Map::MapAreaWorker> &mapAreaWorker);

    void setScheme(const std::shared_ptr<TM::Scheme::Scheme> &scheme);

    void setFocus(const std::shared_ptr<TM::Focus::Focus> &focus);

    std::shared_ptr<TM::Scheme::Scheme> scheme() const;

    std::shared_ptr<TM::Focus::Focus> focus() const;

    void setCalculationTime(int calculationTime);

    void setIsobath(double isobath);

signals:

    void finished();

    void readedFinished();

    void updateTime(int currentTime);

public slots:

    void execute();

    void readBathymetryFromFile();

private:
    QString m_bathymetryPath;
    std::shared_ptr<TM::Map::MapAreaWorker> m_mapAreaWorker;
    std::shared_ptr<TM::Scheme::Scheme> m_scheme;
    std::shared_ptr<TM::Focus::Focus> m_focus;
    bool m_readed;
    ThreadCommand m_command;
    int m_updateTime;
    int m_calculationTime;
    double m_isobath;
};

#endif // TSUNAMIWORKER_H
