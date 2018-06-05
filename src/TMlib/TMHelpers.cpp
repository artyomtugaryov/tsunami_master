#include <TMlib/TMHelpers.h>
#include <QtGui/QImage>
#include <PlotLib/Plot2d.h>

namespace {
    const int Width = 300;
    const int Height = 20;
}

template <typename DataType>
void saveMapAreaAsImage(const std::shared_ptr<TM::Map::RectangleMapArea<DataType>> &area,
                        const std::string &savePath,
                        const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &bath) {
    area->setStartLongitude(bath->startLongitude());
    area->setStartLatitude(bath->startLatitude());
    area->setSizeLongitude(bath->sizeLongitude());
    area->setSizeLatitude(bath->sizeLatitude());
    area->setStepLongitude(bath->stepLongitude());
    area->setStepLatitude(bath->stepLatitude());
    std::shared_ptr<QImage> plotImage =
            std::make_shared<QImage>(bath->sizeLongitude() + Width, bath->sizeLatitude() + Height, QImage::Format_RGB32);
    PlotLib::Plot2d plot;

    plot.setImage(plotImage.get());
    plot.setColorbar(true);
    plot.setRegion(QRectF( QPointF(bath->startLongitude(),
                                   bath->startLatitude()),
                           QPointF(bath->endLongitude(),
                                   bath->endLatitude())));

    plot.setWindow(QRect(0, 0, bath->sizeLongitude() + Width, bath->sizeLatitude() + Height));

    PlotLib::ColorMap colorMap({{0, QColor(0, 91, 65)},
                                {200, QColor(201, 180, 102)},
                                {800, QColor(160, 55, 0)},
                                {1500, QColor(121, 83, 83)},
                                {6000, QColor(214, 214, 214)}});
    area->saveAsTextFile("a.dat", 1);
    PlotLib::ColorMap etaColorBarMap({{-3, QColor(38, 0, 255)},
                                      {-0.1, QColor(222, 255, 248)},
                                      {0, QColor(222, 255, 248)},
                                      {1, QColor(128, 0, 128)},
                                      {2, QColor(255, 0, 0)},
                                      {3, QColor(255, 128, 0)},
                                      {8, QColor(255, 255, 0)},
                                      {11, QColor(0, 255, 0 )}});


    colorFunc2D f = [&etaColorBarMap, &colorMap, &area, &bath](double x, double y)->QColor {
        QColor c;
        double data = area->getDataByIndex(x, y);

        if ((data < 0.000000001 || data > -0.000000001) && bath->getDataByPoint(x, y) > 0) {
            c = bath ? colorMap.getColor(bath->getDataByPoint(x, y)) : QColor(255, 255, 255);
        }
        else
        {
            c = etaColorBarMap.getColor(area->getDataByPoint(x, y));
        }
        return c;
    };
    plot.plotColorFunction(f);

    plot.setAxisX(true);
    plot.setAxisY(true);
    plot.drawAxis(28);
    plot.drawGrid(false, 28, 1, 0, 2, 0);

    std::vector<double> ticks;
    for(int i = etaColorBarMap.min(); i < etaColorBarMap.max(); i++) {
        ticks.push_back(i);
    }
    plot.drawColorbar(etaColorBarMap, ticks, 22);

    plotImage->save(QString::fromStdString(savePath), "PNG");
}


///Implementations
template
void saveMapAreaAsImage(const std::shared_ptr<TM::Map::RectangleMapArea<TM::Map::TypesCells>> &,
                        const std::string &,
                        const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &);

template
void saveMapAreaAsImage(const std::shared_ptr<TM::Map::RectangleMapArea<double>> &,
                        const std::string &,
                        const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &);
