#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ApplicationGUI.h"

int main(int argc, char *argv[])
{
    ApplicationGUI application(argc, argv);
//    std::shared_ptr<TM::Map::MapAreaWorker>mapAreaWorker = std::make_shared<TM::Map::MapAreaWorker>();
//    mapAreaWorker->setBathymetryPath("C:/Users/atugarev/Downloads/work.dat", true);
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QLatin1String("qrc:/Resources/Main.qml")));
    return application.exec();
}
