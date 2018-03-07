#include "TsunamiManager/TsunamiPlotProvider.h"
#include "TsunamiManager/TsunamiPlotData.h"
#include <QDebug>

namespace {
const int Width = 300;
const int Height = 20;
const int scaleValue = 630;
}

TsunamiManagerInfo::TsunamiPlotProvider::TsunamiPlotProvider(TsunamiManagerInfo::TsunamiData *data,
                                                             std::shared_ptr<TM::Map::MapAreaWorker> mapAreaWorker) :
    QQuickImageProvider(QQuickImageProvider::Image),
    m_plot(QSharedPointer<PlotLib::Plot2d>(new Plot2d())),
    m_tsunamiData(data),
    m_mapAreaWorker(std::shared_ptr<TM::Map::MapAreaWorker>(mapAreaWorker)),
    m_colorBarMap(new PlotLib::ColorMap({{-3, QColor(38, 0, 255)},
                                         {-0.1, QColor(222, 255, 248)},
                                         {0, QColor(222, 255, 248)},
                                         {1, QColor(128, 0, 128)},
                                         {3, QColor(255, 0, 0)},
                                         {5, QColor(255, 128, 0)},
                                         {8, QColor(255, 255, 0)},
                                         {11, QColor(0, 255, 0 )}}))
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
        if(static_cast<int>(m_tsunamiData->sizeX()) != m_plotImage->width() - Width ||
                static_cast<int>(m_tsunamiData->sizeY()) != m_plotImage->height() - Height)
        {
            delete m_plotImage;
            setPlotImageSize(m_tsunamiData->sizeX(), m_tsunamiData->sizeY());
        }
        if(m_plotImage->width() != 0 && m_plotImage->height() != 0)
        {
            plotBathametry();
        }
    }
    else
    {
        return QImage(1,1,QImage::Format_RGB32);
    }

    if (m_plotImage->width() > scaleValue && m_plotImage->height() > scaleValue)
    {
        int w, h;
        double coef;
        coef = m_plotImage->width() > m_plotImage->height()
                ? static_cast<double>(m_plotImage->width()) / scaleValue
                : static_cast<double>(m_plotImage->height()) / scaleValue;
        w = static_cast<int> (static_cast<double>(m_plotImage->width()) / coef + 0.5);
        h = static_cast<int> (static_cast<double>(m_plotImage->height()) / coef + 0.5);
        QImage requestImage = m_plotImage->scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        requestImage.save(QString("test2.png"), "PNG");
        return requestImage;
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

void TsunamiManagerInfo::TsunamiPlotProvider::setMapAreaWorker(const std::shared_ptr<TM::Map::MapAreaWorker> &mapAreaWorker)
{
    m_mapAreaWorker.reset();
    m_mapAreaWorker = mapAreaWorker;
}

void TsunamiManagerInfo::TsunamiPlotProvider::setEta(const std::shared_ptr<TM::Map::MapArea<double> > &eta)
{
    m_eta.reset();
    m_eta = eta;
}

void TsunamiManagerInfo::TsunamiPlotProvider::setColorBarMap(const std::shared_ptr<PlotLib::ColorMap> &colorBarMap)
{
    m_colorBarMap.reset();
    m_colorBarMap = colorBarMap;
}

void TsunamiManagerInfo::TsunamiPlotProvider::plotBathametry()
{
    m_plot->setColorbar(true);
    m_plot->setRegion(QRectF( QPointF(m_tsunamiData->startX() + m_tsunamiData->stepX() / 2.,
                                      m_tsunamiData->startY() + m_tsunamiData->stepY() / 2.),
                              QPointF(m_tsunamiData->endX() - m_tsunamiData->stepX() / 2.,
                                      m_tsunamiData->endY() - m_tsunamiData->stepY() / 2.)));

    m_plot->setWindow(QRect(0, 0, m_tsunamiData->sizeX() + 300, m_tsunamiData->sizeY() + 20));
    ColorMap colorMap({{0, QColor(0, 91, 65)},
                       {200, QColor(201, 180, 102)},
                       {800, QColor(160, 55, 0)},
                       {1500, QColor(121, 83, 83)},
                       {6000, QColor(214, 214, 214)}});
    colorFunc2D f = [&colorMap, this](double x, double y)->QColor{
        QColor c;
        double data = m_mapAreaWorker->bathymetry()->getDataByPoint(x, y);

        if (m_eta != NULL)
        {
            m_eta->getDataByPoint(x, y);
        }
        if (data > 0.0) {
            c = colorMap.getColor(data);
        }
        else
        {
            double eta = 0;
            if(m_eta)
            {
                eta = m_eta->getDataByPoint(x, y);
            }
            c = m_colorBarMap->getColor(eta);
        }
        return c;
    };

    m_plot->plotColorFunction(f);
    m_plot->setAxisX(true);
    m_plot->setAxisY(true);
    m_plot->setAxisLabelY("N");
    m_plot->setAxisLabelX("E");
    m_plot->drawAxis(28);
    m_plot->drawGrid(false, 28, 1, 0, 2, 0);

    std::vector<double> ticks;
    for(int i = m_colorBarMap->min(); i < m_colorBarMap->max(); i++) {
        ticks.push_back(i);
    }
    m_plot->drawColorbar(*m_colorBarMap, ticks, 22);
}
