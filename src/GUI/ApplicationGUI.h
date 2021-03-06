#ifndef APPLICATIONGUI_H
#define APPLICATIONGUI_H

#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include <QThread>
#include "SourceGUI.h"

class ApplicationGUI : public QGuiApplication
{
    Q_OBJECT

public:
    ApplicationGUI(int &argc, char **argv);
    virtual ~ApplicationGUI();
    void setPositionByCenter();
signals:
    void readBathymetryFromFile();
private:
    QQuickView *m_view;
    SourceGUI* m_sourceGUI;
    QThread *m_calculationThread;
};

#endif // APPLICATIONGUI_H
