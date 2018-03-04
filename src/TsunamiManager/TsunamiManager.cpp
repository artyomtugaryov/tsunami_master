#include "TsunamiManager/TsunamiManager.h"
#include "PlotLib/Plot2d.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace TsunamiManagerInfo;

TsunamiManager::TsunamiManager(QObject *parent) :
    QObject(parent),
    m_tsunamiData(new TsunamiManagerInfo::TsunamiData(this)),
    m_mapAreaWorker(std::make_shared<TM::Map::MapAreaWorker>()),
    m_scheme(std::make_shared<TM::Scheme::TMScheme24>()),
    m_focus(std::make_shared<TM::TMFocus>()),
    m_signal(std::make_shared<TM::TMSignal>()),
    m_timemanager(std::make_shared<TM::TMTimeManager>()),
    m_plotProvider(new TsunamiPlotProvider(m_tsunamiData, m_mapAreaWorker)),
    m_tsunamiWorker(new TsunamiWorker(m_mapAreaWorker, m_scheme, m_focus, m_timemanager, m_signal)),
    m_tsunamiWorkerThread(new QThread),
    m_plot(new Plot2d()),
    m_currentCalculationTime(0)
{

    m_bathymetryImage = nullptr;

    m_tsunamiWorker->moveToThread(m_tsunamiWorkerThread);
    connect(m_tsunamiData->plotData(), &TsunamiPlotData::colorBarChanged,
            this, &TsunamiManager::colorBarProvide);
    connect(m_tsunamiWorkerThread, SIGNAL(started()),
            m_tsunamiWorker, SLOT(execute()));
    connect(m_tsunamiWorker, SIGNAL(finished()), m_tsunamiWorkerThread, SLOT(terminate()));
    connect(m_tsunamiWorker, SIGNAL(readedFinished()), this, SLOT(tsunamiWorkerThreadReaded()));
    //connect(m_tsunamiWorker, SIGNAL(updateTime(int)), this, SLOT(isUpdateTime(int)));
    m_timemanager->setSendingTimeStep(10);
    qRegisterMetaType<std::shared_ptr<TM::Map::MapArea<double>>>("std::shared_ptr<TM::Map::MapArea<double>>");
    connect(m_signal.get(), &TM::TMSignal::signalUpdate, this, &TsunamiManagerInfo::TsunamiManager::isUpdateTime);
    loadInitDataFromJson();
}

TsunamiData *TsunamiManager::tsunamiData() const
{
    return m_tsunamiData;
}

void TsunamiManager::readBathymetryFromFile(QString path)
{
    m_tsunamiData->setReaded(false);
    if (m_mapAreaWorker.get() != NULL)
    {
        m_mapAreaWorker.reset();
        m_mapAreaWorker = std::make_shared<TM::Map::MapAreaWorker>();
        m_tsunamiWorker->setMapAreaWorker(m_mapAreaWorker);
        m_plotProvider->setMapAreaWorker(m_mapAreaWorker);
    }
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    path = path.remove("file:///");
#else
    path = path.remove("file://");
#endif
    m_tsunamiWorker->setBathymetryPath(path);
    m_tsunamiData->setBathymetryPath(path);
    m_tsunamiWorker->setCommand(TsunamiWorker::ThreadCommand::ReadBathymetry);
    m_tsunamiWorkerThread->start();
}

void TsunamiManager::readBrickDataFromFile(QString path)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    path = path.remove("file:///");
#else
    path = path.remove("file://");
#endif
    m_tsunamiData->setBrickPath(path);
    if (m_focus)
    {
        m_focus.reset();
    }
    m_focus = std::make_shared<TM::TMFocus>(path.toStdString());
    m_tsunamiWorker->setFocus(m_focus);
}

void TsunamiManager::startCalculation()
{
    if (m_tsunamiWorker->readed()
            && m_tsunamiWorkerThread->isFinished()
            && m_focus)
    {
        if (m_scheme)
        {
            m_scheme.reset();
        }
        m_scheme = std::make_shared<TM::Scheme::TMScheme24>();
        m_tsunamiWorker->setScheme(m_scheme);
        m_tsunamiWorker->setCommand(TsunamiWorker::ThreadCommand::RunCalculation);
        m_tsunamiWorkerThread->start();
    }
}

void TsunamiManager::tsunamiWorkerThreadReaded()
{
    m_tsunamiWorkerThread->terminate();
    m_tsunamiData->setReaded(m_tsunamiWorker->readed());
    if (m_tsunamiWorker->readed())
    {
        m_tsunamiData->setStartX(m_mapAreaWorker->bathymetry()->startX());
        m_tsunamiData->setStartY(m_mapAreaWorker->bathymetry()->startY());

        m_tsunamiData->setEndX(m_mapAreaWorker->bathymetry()->endX());
        m_tsunamiData->setEndY(m_mapAreaWorker->bathymetry()->endY());

        m_tsunamiData->setSizeX(m_mapAreaWorker->bathymetry()->sizeX());
        m_tsunamiData->setSizeY(m_mapAreaWorker->bathymetry()->sizeY());

        m_tsunamiData->setStepX(m_mapAreaWorker->bathymetry()->stepX());
        m_tsunamiData->setStepY(m_mapAreaWorker->bathymetry()->stepY());

        m_plotProvider->setPlotImageSize(m_tsunamiData->sizeX(), m_tsunamiData->sizeY());

        if (m_bathymetryImage != nullptr) delete m_bathymetryImage;
        m_bathymetryImage = new QImage(m_tsunamiData->sizeX() + 300, m_tsunamiData->sizeY() + 20, QImage::Format_RGB32);
        m_plot->setImage(m_bathymetryImage);
        m_plotProvider->requestImage(QString("1"), NULL, QSize(0,0));
        emit imageUpdate();
    }
}

void TsunamiManager::isUpdateTime(std::shared_ptr<TM::Map::MapArea<double> > eta)
{
    m_eta.reset();
    m_eta = eta;
    m_plotProvider->setEta(m_eta);
    emit imageUpdate();
}

std::shared_ptr<TM::Map::MapArea<double> > TsunamiManager::eta() const
{
    return m_eta;
}

void TsunamiManager::quickStart()
{
    if (m_tsunamiWorker->bathymetryPath().size() > 5)
    {
        readBathymetryFromFile(m_tsunamiWorker->bathymetryPath());
    }
}

void TsunamiManager::colorBarProvide(const std::shared_ptr<PlotLib::ColorMap> &colorBarMap)
{
    m_plotProvider->setColorBarMap(colorBarMap);
    emit imageUpdate();
}

void TsunamiManager::saveInitDataToJson()
{
    QFile saveFile("INIT.json");

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
    }

    QJsonObject init;

    QJsonObject paths;
    paths["bathymetryPath"] = m_tsunamiData->bathymetryPath();
    paths["brickPath"] = m_tsunamiData->brickPath();
    paths["imageSavePath"] = m_tsunamiData->imageSavePath();
    paths["distributionSavePath"] = m_tsunamiData->maxDistributionSavePath();
    init["paths"] = paths;

    QJsonObject mapData;
    mapData["sizeX"] = static_cast<int> (m_tsunamiData->sizeX());
    mapData["sizeY"] = static_cast<int> ( m_tsunamiData->sizeY());
    mapData["startX"] = m_tsunamiData->startX();
    mapData["startY"] = m_tsunamiData->startY();
    mapData["endX"] = m_tsunamiData->endX();
    mapData["endY"] = m_tsunamiData->endY();
    mapData["stepX"] = m_tsunamiData->stepX();
    mapData["stepY"] = m_tsunamiData->stepY();
    init["mapData"] = mapData;

    QJsonDocument saveDoc(init);
    saveFile.write(saveDoc.toJson());
}

void TsunamiManager::loadInitDataFromJson()
{
    QFile loadFile(QStringLiteral("INIT.json"));

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open init file.");
        return;
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject init = loadDoc.object();
    QJsonObject paths = init["paths"].toObject();

    QString tmp = paths["bathymetryPath"].toString();
    if (!tmp.isEmpty())
    {
        m_tsunamiWorker->setBathymetryPath(tmp);
        m_tsunamiData->setBathymetryPath(tmp);
    }

    tmp = paths["brickPath"].toString();
    if (!tmp.isEmpty())
    {
        m_tsunamiData->setBrickPath(tmp);
    }

    tmp = paths["imageSavePath"].toString();
    if (!tmp.isEmpty())
    {
        m_tsunamiData->setImageSavePath(tmp);
    }

    tmp = paths["distributionSavePath"].toString();
    if (!tmp.isEmpty())
    {
        m_tsunamiData->setMaxDistributionSavePath(tmp);
    }

    QJsonObject mapData = init["mapData"].toObject();
    m_tsunamiData->setStartX(mapData["startX"].toDouble());
    m_tsunamiData->setStartY(mapData["startY"].toDouble());
    m_tsunamiData->setEndX(mapData["endX"].toDouble());
    m_tsunamiData->setEndY(mapData["endY"].toDouble());
    m_tsunamiData->setSizeX(mapData["sizeX"].toInt());
    m_tsunamiData->setSizeY(mapData["sizeY"].toInt());
    m_tsunamiData->setStepX(mapData["stepX"].toDouble());
    m_tsunamiData->setStepY(mapData["stepY"].toDouble());
}

TsunamiPlotProvider *TsunamiManager::plotProvider() const
{
    return m_plotProvider;
}

void TsunamiManager::setPlotProvider(TsunamiPlotProvider *plotProvider)
{
    m_plotProvider = plotProvider;
}

int TsunamiManager::currentCalculationTime()
{
    return m_currentCalculationTime;
}
