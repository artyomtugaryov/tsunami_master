#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ApplicationGUI.h"

int main(int argc, char *argv[])
{
    ApplicationGUI application(argc, argv);

    return application.exec();

}
