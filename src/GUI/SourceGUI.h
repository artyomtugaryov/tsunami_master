#ifndef SOURCEGUI_H
#define SOURCEGUI_H

#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include <QThread>
#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMException.h>
#include <TsunamiManager/TsunamiManager.h>

class SourceGUI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TsunamiManagerInfo::TsunamiManager* tsunamiManager READ TsunamiManager CONSTANT)

public:
    SourceGUI(QObject *parent = 0);
    virtual ~SourceGUI();

    TsunamiManagerInfo::TsunamiManager* TsunamiManager() const;
public slots:
    void initTsunamiMaster();
private:
    TsunamiManagerInfo::TsunamiManager* m_tsunamiManager;
    QThread* m_tsunamiManagerThread;
};

#endif // SOURCEGUI_H
