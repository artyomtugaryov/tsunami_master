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
    Q_PROPERTY(TsunamiManagerInfo::TsunamiManager* tsunamiManager READ tsunamiManager CONSTANT)

public:
    SourceGUI(QObject *parent = 0);
    virtual ~SourceGUI();

    TsunamiManagerInfo::TsunamiManager* tsunamiManager() const;
    Q_INVOKABLE void startReadFromFile(const QString &path);

private:
    TsunamiManagerInfo::TsunamiManager* m_tsunamiManager;
};

#endif // SOURCEGUI_H
