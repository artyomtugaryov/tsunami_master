#include "TsunamiManager/TsunamiPlotProvider.h"
#include "TsunamiManager/TsunamiPlotData.h"

#include <TMlib/mareograph.h>

#include <QDebug>

namespace {
const int Width = 300;
const int Height = 20;
const int scaleValue = 630;
}

using namespace TsunamiManagerInfo;

TsunamiPlotProvider::TsunamiPlotProvider(TsunamiManagerInfo::TsunamiData *data,
                                                             std::shared_ptr<TM::Map::MapAreaWorker> mapAreaWorker) :
    QQuickImageProvider(QQuickImageProvider::Image, QQmlImageProviderBase::ForceAsynchronousImageLoading),
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
                                         {11, QColor(0, 255, 0 )}})),
    m_plotting(false)
{
    m_plotImage = nullptr;
}

QImage TsunamiPlotProvider::requestImage(const QString &id,
                                         QSize *size,
                                         const QSize &requestedSize)
{
    m_plotting = true;
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
        requestImage.save(id + QString(".png"),"PNG");
        m_plotting = false;
        return requestImage;
    }
    m_plotting = false;
    return *m_plotImage;
}

TsunamiData *TsunamiManagerInfo::TsunamiPlotProvider::TsunamiData() const
{
    return m_tsunamiData;
}

void TsunamiPlotProvider::setTsunamiData(TsunamiManagerInfo::TsunamiData *TsunamiData)
{
    m_tsunamiData = TsunamiData;
}

void TsunamiPlotProvider::setPlotImageSize(int width, int height)
{
    if (m_plotImage != nullptr) {
        delete m_plotImage;
    }
    m_plotImage = new QImage(width + Width, height + Height, QImage::Format_RGB32);
    m_plot->setImage(m_plotImage);
}

void TsunamiPlotProvider::setMapAreaWorker(const std::shared_ptr<TM::Map::MapAreaWorker> &mapAreaWorker)
{
    m_mapAreaWorker.reset();
    m_mapAreaWorker = mapAreaWorker;
}

void TsunamiPlotProvider::setEta(const std::shared_ptr<TM::Map::MapArea<double>> &eta)
{
    m_eta.reset();
    m_eta = eta;
}

void TsunamiPlotProvider::setColorBarMap(const std::shared_ptr<PlotLib::ColorMap> &colorBarMap)
{
    m_colorBarMap.reset();
    m_colorBarMap = colorBarMap;
}

void TsunamiPlotProvider::plotBathametry()
{
    m_plot->setColorbar(true);
    m_plot->setRegion(QRectF(QPointF(m_tsunamiData->startX(),
                                      m_tsunamiData->startY()),
                              QPointF(m_tsunamiData->endX(),
                                      m_tsunamiData->endY())));

    m_plot->setWindow(QRect(0, 0, m_tsunamiData->sizeX() + 300, m_tsunamiData->sizeY() + 20));
    ColorMap colorMap({{0, QColor(0, 91, 65)},
                       {200, QColor(201, 180, 102)},
                       {800, QColor(160, 55, 0)},
                       {1500, QColor(121, 83, 83)},
                       {6000, QColor(214, 214, 214)}});
    if(m_eta)
    {
        m_eta->setStartX(m_mapAreaWorker->bathymetry().startX());
        m_eta->setStartY(m_mapAreaWorker->bathymetry().startY());
        m_eta->setSizeX(m_mapAreaWorker->bathymetry().sizeX());
        m_eta->setSizeY(m_mapAreaWorker->bathymetry().sizeY());
        m_eta->setStepX(m_mapAreaWorker->bathymetry().stepX());
        m_eta->setStepY(m_mapAreaWorker->bathymetry().stepY());
    }
    colorFunc2D f = [&colorMap, this](double x, double y)->QColor {
        QColor c;

        double data = m_mapAreaWorker->bathymetry().getDataByPoint(x, y);

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

    if(m_mapAreaWorker->mareoghraphs().size() != 0)
    {
        for(auto mareoghraph:m_mapAreaWorker->mareoghraphs())
        {
            m_plot->drawPointByIndex(mareoghraph.getLongitude(),
                                     mareoghraph.getLatitude());
        }
    }
}

bool TsunamiPlotProvider::plotting() const
{
    return m_plotting;
}
