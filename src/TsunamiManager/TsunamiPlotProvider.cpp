#include "TsunamiManager/TsunamiPlotProvider.h"
#include <QDebug>

namespace {
const int Width = 300;
const int Height = 20;
}

TsunamiManagerInfo::TsunamiPlotProvider::TsunamiPlotProvider(TsunamiManagerInfo::TsunamiData *data,
                                                             QSharedPointer<TM::Map::MapAreaWorker> mapAreaWorker) :
    QQuickImageProvider(QQuickImageProvider::Image),
    m_plot(QSharedPointer<PlotLib::Plot2d>(new Plot2d())),
    m_tsunamiData(data),
    m_mapAreaWorker(QSharedPointer<TM::Map::MapAreaWorker>(mapAreaWorker))
{
    m_plotImage = nullptr;
}

QImage TsunamiManagerInfo::TsunamiPlotProvider::requestImage(const QString &id,
                                                             QSize *size,
                                                             const QSize &requestedSize)
{
    Q_UNUSED(id);
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

    if(m_plotImage != nullptr)
    {
        qDebug() << "Point 1";
        if(static_cast<int>(m_tsunamiData->sizeX()) != m_plotImage->width() - Width ||
                static_cast<int>(m_tsunamiData->sizeY()) != m_plotImage->height() - Height)
        {
            delete m_plotImage;
            setPlotImageSize(m_tsunamiData->sizeX(), m_tsunamiData->sizeY());
        }
        if(m_plotImage->width() != 0 && m_plotImage->height() != 0)
        {
            qDebug() << "Point 2";
            plotBathametry();
        }
    }
    else
    {
        return QImage(1,1,QImage::Format_RGB32);
    }

    return *m_plotImage;
}

TsunamiManagerInfo::TsunamiData *TsunamiManagerInfo::TsunamiPlotProvider::TsunamiData() const
{
    return m_tsunamiData;
}

void TsunamiManagerInfo::TsunamiPlotProvider::setTsunamiData(TsunamiManagerInfo::TsunamiData *TsunamiData)
{
    m_tsunamiData = TsunamiData;
}

void TsunamiManagerInfo::TsunamiPlotProvider::setPlotImageSize(int width, int height)
{
    if (m_plotImage != nullptr) {
        delete m_plotImage;
    }
    m_plotImage = new QImage(width + Width, height + Height, QImage::Format_RGB32);
    m_plot->setImage(m_plotImage);
}

void TsunamiManagerInfo::TsunamiPlotProvider::setMapAreaWorker(const QSharedPointer<TM::Map::MapAreaWorker> &mapAreaWorker)
{
    m_mapAreaWorker.clear();
    m_mapAreaWorker = mapAreaWorker;
}

void TsunamiManagerInfo::TsunamiPlotProvider::plotBathametry()
{
    qDebug() << "Point 3";
    m_plot->setColorbar(true);
    m_plot->setRegion(QRectF( QPointF(m_tsunamiData->startX() + m_tsunamiData->stepX() / 2.,
                                      m_tsunamiData->startY() + m_tsunamiData->stepY() / 2.),
                              QPointF(m_tsunamiData->endX() - m_tsunamiData->stepX() / 2.,
                                      m_tsunamiData->endY() - m_tsunamiData->stepY() / 2.)));

    qDebug() << "Point 3.1";
    m_plot->setWindow(QRect(0, 0, m_tsunamiData->sizeX() + 300, m_tsunamiData->sizeY() + 20));
    qDebug() << "Point 4";
    ColorMap colorMap({{0, QColor(0, 255, 0)}, {3000, QColor(0, 70, 0)}});
    qDebug() << "Point 5";
    colorFunc2D f = [&colorMap, this](double x, double y)->QColor{
        QColor c;
        double data = m_mapAreaWorker->bathymetry()->getDataByPoint(x, y);

        if (data >= 0.0) {
            c = colorMap.getColor(data);
        }
        else if (data < 0) c = QColor(38, 225, 255);
        return c;
    };
    qDebug() << "Point 6";
    m_plot->plotColorFunction(f);
    qDebug() << "Point 6.1";
    m_plot->setAxisX(true);
    m_plot->setAxisY(true);
    m_plot->setAxisLabelY("N");
    m_plot->setAxisLabelX("E");
    m_plot->drawAxis(28);
    qDebug() << "Point 7";
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
    qDebug() << "Point 8";
    m_plot->drawColorbar(colorbarMap, ticks, 22);
}
