#include <TMlib/helpers.h>
#include <QtGui/QImage>
#include <PlotLib/Plot2d.h>

namespace {
    const int Width = 300;
    const int Height = 20;
}

template <typename DataType>
void saveMapAreaAsImage(const std::shared_ptr<TM::Map::MapArea<DataType>> &area,
                        const std::string &savePath,
                        const std::shared_ptr<const TM::Map::MapArea<double>> &bath,
                        const bool &drawBath) {
    area->setStartX(bath->startX());
    area->setStartY(bath->startY());
    area->setSizeX(bath->sizeX());
    area->setSizeY(bath->sizeY());
    area->setStepX(bath->stepX());
    area->setStepY(bath->stepY());
    std::shared_ptr<QImage> plotImage =
            std::make_shared<QImage>(bath->sizeX() + Width, bath->sizeY() + Height, QImage::Format_RGB32);
    PlotLib::Plot2d plot;
    plot.setImage(plotImage.get());
    plot.setRegion(QRectF( QPointF(bath->startX(),
                                   bath->startY()),
                           QPointF(bath->endX(),
                                   bath->endY())));

    plot.setWindow(QRect(0, 0, bath->sizeX() + Width, bath->sizeY() + Height));

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
    plotImage->save(QString::fromStdString(savePath), "PNG");
}


///Implementations
template
void saveMapAreaAsImage(const std::shared_ptr<TM::Map::MapArea<TM::Scheme::types_cells>> &,
                        const std::string &,
                        const std::shared_ptr<const TM::Map::MapArea<double>> &,
                        const bool &);