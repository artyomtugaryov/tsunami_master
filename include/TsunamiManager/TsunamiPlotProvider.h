#ifndef TSUNAMIPLOTPROVIDER_H
#define TSUNAMIPLOTPROVIDER_H

#include "TsunamiManager/TsunamiData.h"

#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMException.h>
#include <PlotLib/Plot2d.h>
#include <PlotLib/ColorMap.h>

#include <QObject>
#include <QQuickImageProvider>
#include <QImage>
#include <QSharedPointer>
#include <memory>

using namespace PlotLib;

namespace TsunamiManagerInfo {
class TsunamiPlotProvider : public QQuickImageProvider
{
public:
    TsunamiPlotProvider(TsunamiManagerInfo::TsunamiData *data, std::shared_ptr<TM::Map::MapAreaWorker> mapAreaWorker);
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    TsunamiManagerInfo::TsunamiData *TsunamiData() const;
    void setTsunamiData(TsunamiManagerInfo::TsunamiData *TsunamiData);
    void setPlotImageSize(int width, int height);
    void setMapAreaWorker(const std::shared_ptr<TM::Map::MapAreaWorker> &mapAreaWorker);
    void setEta(const std::shared_ptr<TM::Map::MapArea<double> > &eta);
    void setColorBarMap(const std::shared_ptr<PlotLib::ColorMap> &colorBarMap);
private:
    void plotBathametry();

    QImage* m_plotImage;
    QSharedPointer<Plot2d> m_plot;
    ColorMap m_bathymetryMap;
    ColorMap m_waterMap;
    TsunamiManagerInfo::TsunamiData *m_tsunamiData;
    std::shared_ptr<TM::Map::MapAreaWorker> m_mapAreaWorker;
    std::shared_ptr<TM::Map::MapArea<double> > m_eta;
    std::shared_ptr<PlotLib::ColorMap> m_colorBarMap;
};
}
#endif // TSUNAMIPLOTPROVIDER_H
