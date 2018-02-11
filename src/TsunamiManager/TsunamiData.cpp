#include "TsunamiManager/TsunamiData.h"

namespace
{
QLatin1String PathNone("None");
}

using namespace TsunamiManagerInfo;

TsunamiData::TsunamiData(QObject *parent) :
    QObject(parent),
    m_sizeX(0),
    m_sizeY(0),
    m_startX(0),
    m_startY(0),
    m_endX(0),
    m_endY(0),
    m_stepX(0),
    m_stepY(0),
    m_bathymetryPath(PathNone),
    m_brickPath(PathNone),
    m_imageSavePath(PathNone),
    m_maxDistributionSavePath(PathNone),
    m_readed(false),
    m_plotData(new TsunamiPlotData())
{
}

TsunamiData::~TsunamiData() {}

uint TsunamiData::sizeX() const
{
    return m_sizeX;
}

uint TsunamiData::sizeY() const
{
    return m_sizeY;
}

double TsunamiData::startX() const
{
    return m_startX;
}

double TsunamiData::startY() const
{
    return m_startY;
}

double TsunamiData::endX() const
{
    return m_endX;
}

double TsunamiData::endY() const
{
    return m_endY;
}

double TsunamiData::stepX() const
{
    return m_stepX;
}

double TsunamiData::stepY() const
{
    return m_stepY;
}

QString TsunamiData::bathymetryPath() const
{
    return m_bathymetryPath;
}

QString TsunamiData::brickPath() const
{
    return m_brickPath;
}

QString TsunamiData::imageSavePath() const
{
    return m_imageSavePath;
}

QString TsunamiData::maxDistributionSavePath() const
{
    return m_maxDistributionSavePath;
}

void TsunamiData::setSizeX(uint size) {
    if (m_sizeX != size) {
        m_sizeX = size;
        emit sizeXChanged(size);
    }
}

void TsunamiData::setSizeY(uint size) {
    if (m_sizeY != size) {
        m_sizeY = size;
        emit sizeYChanged(size);
    }
}

void TsunamiData::setStartX(double start) {
    if (m_startX != start) {
        m_startX = start;
        emit startXChanged(start);
    }
}

void TsunamiData::setStartY(double start) {
    if (m_startY != start) {
        m_startY = start;
        emit startYChanged(start);
    }
}

void TsunamiData::setEndX(double end) {
    if (m_endX != end) {
        m_endX = end;
        emit endXChanged(end);
    }
}

void TsunamiData::setEndY(double end) {
    if (m_endY != end) {
        m_endY = end;
        emit endYChanged(end);
    }
}

void TsunamiData::setStepX(double step) {
    if (m_stepX != step) {
        m_stepX = step;
        emit stepXChanged(step);
    }
}

void TsunamiData::setStepY(double step) {
    if (m_stepY != step) {
        m_stepY = step;
        emit stepYChanged(step);
    }
}

void TsunamiData::setImageSavePath(QString imageSavePath)
{
    imageSavePath = imageSavePath.remove("file:///");
    if (m_imageSavePath == imageSavePath)
        return;

    m_imageSavePath = imageSavePath;
    emit imageSavePathChanged();
}

void TsunamiData::setMaxDistributionSavePath(QString maxDistributionSavePath)
{
    maxDistributionSavePath = maxDistributionSavePath.remove("file:///");
    if (m_maxDistributionSavePath == maxDistributionSavePath)
    {
        return;
    }

    m_maxDistributionSavePath = maxDistributionSavePath;
    emit maxDistributionSavePathChanged();
}

void TsunamiData::setReaded(bool readed)
{
    if (m_readed == readed)
    {
        return;
    }
    m_readed = readed;
    emit readedChanged();
}

TsunamiPlotData *TsunamiData::plotData() const
{
    return m_plotData;
}

void TsunamiData::setBrickPath(const QString &brickPath)
{
    m_brickPath = brickPath;
    emit brickPathChanged();
}

bool TsunamiData::readed() const
{
    return m_readed;
}

void TsunamiData::setBathymetryPath(const QString &bathymetryPath)
{
    m_bathymetryPath = bathymetryPath;
    emit bathymetryPathChanged();
}
