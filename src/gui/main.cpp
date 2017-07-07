#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "HDlib/MapAreaWorker.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Map::MapAreaWorker* mapAreaWorker = new Map::MapAreaWorker();
    mapAreaWorker->setBathymetryPath("C:/Users/Tyuntyaev/Documents/GitRoot/work.dat", true);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/Resources/Main.qml")));
    return app.exec();

}
