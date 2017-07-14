#ifndef APPLICATIONGUI_H
#define APPLICATIONGUI_H

#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include <QThread>
//class QQuickView;
//TODO: Create and include SourceGUI class
/*namespace GUI
{
    class SourceGUI;
}*/

class ApplicationGUI : public QGuiApplication
{
    Q_OBJECT

public:
    ApplicationGUI(int &argc, char **argv);
    ~ApplicationGUI();
    void setPositionByCenter();
private:
    QQuickView *m_view;
    QThread *m_calculation;
};

#endif // APPLICATIONGUI_H
