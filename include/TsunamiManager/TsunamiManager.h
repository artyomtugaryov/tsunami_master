#ifndef TSUNAMIMANAGER_H
#define TSUNAMIMANAGER_H

#include "TsunamiData.h"
#include "TsunamiWorker.h"
#include "TsunamiPlotProvider.h"

#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMException.h>
#include <TMlib/TMException.h>
#include <TMlib/TMScheme24.h>
#include <TMlib/TMFocus.h>
#include <PlotLib/Plot2d.h>
#include <PlotLib/ColorMap.h>

#include <QObject>
#include <QSharedPointer>
#include <QThread>
#include <QImage>
#include <memory>

using namespace PlotLib;

namespace TsunamiManagerInfo {

class TsunamiManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(TsunamiData *tsunamiData READ tsunamiData CONSTANT)
    Q_PROPERTY(int currentCalculationTime READ currentCalculationTime NOTIFY currentCalculationTimeChanged)
public:
    TsunamiManager(QObject *parent = nullptr);
    TsunamiData * tsunamiData() const;
    TsunamiPlotProvider *plotProvider() const;
    void setPlotProvider(TsunamiPlotProvider *plotProvider);
    int currentCalculationTime();
    void loadInitDataFromJson();
public slots:
    void readBathymetryFromFile(QString path);
    void readBrickDataFromFile(QString path);
    void startCalculation();
    void tsunamiWorkerThreadReaded();
    void isUpdateTime(int currentTime);
    void saveInitDataToJson();
    void quickStart();
signals:
    void pathChanged();
    void currentCalculationTimeChanged();
    void imageUpdate();
private:
    TsunamiManagerInfo::TsunamiData* m_tsunamiData;
    std::shared_ptr<TM::Map::MapAreaWorker> m_mapAreaWorker;
    TsunamiManagerInfo::TsunamiPlotProvider* m_plotProvider;
    TsunamiWorker* m_tsunamiWorker;
    QThread* m_tsunamiWorkerThread;
    QImage* m_bathymetryImage;
    Plot2d* m_plot;
    int m_currentCalculationTime;
    std::shared_ptr<TM::Scheme::TMScheme24> m_scheme;
};
}
#endif //TSUNAMIMANAGER_H
