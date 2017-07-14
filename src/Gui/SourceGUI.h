#ifndef SOURCEGUI_H
#define SOURCEGUI_H

#include <QObject>
#include <QGuiApplication>
#include <QQuickView>

class SourceGUI : public QObject
{

    Q_OBJECT

public:
    SourceGUI(QObject *parent = 0);
    ~SourceGUI();
private:

};

#endif // SOURCEGUI_H
