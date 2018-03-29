#ifndef TSUNAMIWORKER_H
#define TSUNAMIWORKER_H

#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMException.h>
#include <TMlib/TMScheme24.h>
#include <TMlib/TMTimeManager.h>
#include <TMlib/TMFocus.h>

#include <QObject>
#include <QSharedPointer>
#include <QString>

class TsunamiWorker : public QObject
{
    Q_OBJECT
    Q_ENUMS(ThreadCommand)
public:
    enum ThreadCommand
    {
        None = 0,
        ReadBathymetry,
        RunCalculation
    };
    explicit TsunamiWorker(std::shared_ptr<TM::Map::MapAreaWorker> mapAreaWorker,
                           std::shared_ptr<TM::Scheme::TMScheme> scheme,
                           std::shared_ptr<TM::Focus::Focus> focus,
                           std::shared_ptr<TM::TMTimeManager> timemanager,
                           std::shared_ptr<TM::TMSignal> tmsignal,
                           QObject *parent = 0);
    QString bathymetryPath() const;
    void setBathymetryPath(const QString &path);
    bool readed() const;
    void setCommand(const ThreadCommand &command);
    void runCalculation();
    void setMapAreaWorker(const std::shared_ptr<TM::Map::MapAreaWorker> &mapAreaWorker);

    void setScheme(const std::shared_ptr<TM::Scheme::TMScheme> &scheme);
    void setFocus(const std::shared_ptr<TM::Focus::Focus> &focus);
    std::shared_ptr<TM::Scheme::TMScheme> scheme() const;
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
    std::shared_ptr<TM::Scheme::TMScheme> m_scheme;
    std::shared_ptr<TM::Focus::Focus> m_focus;
    std::shared_ptr<TM::TMTimeManager> m_timemanager;
    std::shared_ptr<TM::TMSignal> m_signal;
    bool m_readed;
    ThreadCommand m_command;
    int m_updateTime;
    int m_calculationTime;
    double m_isobath;
};

#endif // TSUNAMIWORKER_H
