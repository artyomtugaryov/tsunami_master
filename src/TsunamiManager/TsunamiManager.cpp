#include "TsunamiManager/TsunamiManager.h"
#include "PlotLib/Plot2d.h"
#include <QDebug>
TsunamiManagerInfo::TsunamiManager::TsunamiManager(QObject *parent) :
    QObject(parent),
    m_mapData(new TsunamiManagerInfo::MapData(this)),
    m_mapAreaWorker(new TM::Map::MapAreaWorker),
    m_plot(new Plot2d())
{
    m_bathymetryImage = nullptr;
}

TsunamiManagerInfo::MapData *TsunamiManagerInfo::TsunamiManager::mapData() const
{
    return m_mapData;
}

QString TsunamiManagerInfo::TsunamiManager::path() const
{
    return m_path;
}

void TsunamiManagerInfo::TsunamiManager::readBathymetryFromFile()
{
    if (m_mapAreaWorker->setBathymetryPath(m_path.toStdString(), true)) {
        m_mapData->setStartX(m_mapAreaWorker->bathymetry()->startX());
        m_mapData->setStartY(m_mapAreaWorker->bathymetry()->startY());

        m_mapData->setEndX(m_mapAreaWorker->bathymetry()->endX());
        m_mapData->setEndY(m_mapAreaWorker->bathymetry()->endY());

        m_mapData->setSizeX(m_mapAreaWorker->bathymetry()->sizeX());
        m_mapData->setSizeY(m_mapAreaWorker->bathymetry()->sizeY());

        m_mapData->setStepX(m_mapAreaWorker->bathymetry()->stepX());
        m_mapData->setStepY(m_mapAreaWorker->bathymetry()->stepY());

        if (m_bathymetryImage != nullptr) delete m_bathymetryImage;

        m_bathymetryImage = new QImage(m_mapData->sizeX() + 300, m_mapData->sizeY() + 20, QImage::Format_RGB32);
        m_plot->setImage(m_bathymetryImage);
        plotBathametry();
        m_bathymetryImage->save("TEST2.png");
        qDebug() << "Draw";
    }
}

void TsunamiManagerInfo::TsunamiManager::plotBathametry()
{
    m_plot->setColorbar(true);
    m_plot->setRegion(QRectF( QPointF(m_mapData->startX() + m_mapData->stepX() / 2.,
                                      m_mapData->startY() + m_mapData->stepY() / 2.),
                              QPointF(m_mapData->endX() - m_mapData->stepX() / 2.,
                                      m_mapData->endY() - m_mapData->stepY() / 2.)));

    m_plot->setWindow(QRect(0, 0, m_mapData->sizeX() + 300, m_mapData->sizeY() + 20));

    ColorMap colorMap({{0, QColor(0, 255, 0)}, {3000, QColor(0, 70, 0)}});

    colorFunc2D f = [&colorMap, this](double x, double y)->QColor{
        QColor c;
        double data = m_mapAreaWorker->bathymetry()->getDataByPoint(x, y);

        if (data >= 0.0) {
            c = colorMap.getColor(data);
        }
        else if (data < 0) c = QColor(38, 225, 255);
        return c;
    };
    m_plot->plotColorFunction(f);
    m_plot->setAxisX(true);
    m_plot->setAxisY(true);
    m_plot->setAxisLabelY("N");
    m_plot->setAxisLabelX("E");
    m_plot->drawAxis(28);
    m_plot->drawGrid(false, 28, 1, 0, 2, 0);

    ColorMap colorbarMap({{-3, QColor(38, 0, 255)},
                          {-0.1, QColor(222, 255, 248)},
                          {0, QColor(222, 255, 248)},
                          {1, QColor(128, 0, 128)},
                          {3, QColor(255, 0, 0)},
                          {5, QColor(255, 128, 0)},
                          {8, QColor(255, 255, 0)},
                          {11, QColor(0, 255, 0 )}});

    std::vector<double> ticks;
    for(int i = -3; i < 11; i++) {
        ticks.push_back(i);
    }
    m_plot->drawColorbar(colorbarMap, ticks, 22);
}

void TsunamiManagerInfo::TsunamiManager::setPath(QString path)
{
    if (m_path == path)
        return;

    m_path = path.remove("file:///");

    qDebug() << path;
    emit pathChanged();
}
