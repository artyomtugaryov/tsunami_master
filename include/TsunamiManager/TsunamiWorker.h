#ifndef TSUNAMIWORKER_H
#define TSUNAMIWORKER_H

#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMException.h>

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
    explicit TsunamiWorker(std::shared_ptr<TM::Map::MapAreaWorker> mapAreaWorker, QObject *parent = 0);
    QString bathymetryPath() const;
    void setBathymetryPath(const QString &path);
    bool readed() const;
    void setCommand(const ThreadCommand &command);
    void runCalculation();
    void setMapAreaWorker(const std::shared_ptr<TM::Map::MapAreaWorker> &mapAreaWorker);

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
    bool m_readed;
    ThreadCommand m_command;
    int m_updateTime;
};

#endif // TSUNAMIWORKER_H
