#ifndef TSUNAMIWORKER_H
#define TSUNAMIWORKER_H

#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMException.h>
#include <TMlib/TMScheme24.h>
#include <TMlib/TMSignal.h>
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
                           std::shared_ptr<TM::Scheme::TMScheme24> scheme,
                           std::shared_ptr<TM::TMFocus> focus,
                           std::shared_ptr<TM::TMSignal> signal,
                           QObject *parent = 0);
    QString bathymetryPath() const;
    void setBathymetryPath(const QString &path);
    bool readed() const;
    void setCommand(const ThreadCommand &command);
    void runCalculation();
    void setMapAreaWorker(const std::shared_ptr<TM::Map::MapAreaWorker> &mapAreaWorker);

    void setScheme(const std::shared_ptr<TM::Scheme::TMScheme24> &scheme);
    void setFocus(const std::shared_ptr<TM::TMFocus> &focus);
    std::shared_ptr<TM::Scheme::TMScheme24> scheme() const;
    std::shared_ptr<TM::TMFocus> focus() const;

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
    std::shared_ptr<TM::Scheme::TMScheme24> m_scheme;
    std::shared_ptr<TM::TMFocus> m_focus;
    std::shared_ptr<TM::TMSignal> m_signal;
    bool m_readed;
    ThreadCommand m_command;
    int m_updateTime;
};

#endif // TSUNAMIWORKER_H
