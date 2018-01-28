#include "TsunamiManager/TsunamiData.h"

namespace
{
QLatin1String PathNone("None");
}

TsunamiManagerInfo::TsunamiData::TsunamiData(QObject *parent) :
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
    m_maxDistributionSavePath(PathNone)
{
}

TsunamiManagerInfo::TsunamiData::~TsunamiData() {}

uint TsunamiManagerInfo::TsunamiData::sizeX() const
{
    return m_sizeX;
}

uint TsunamiManagerInfo::TsunamiData::sizeY() const
{
    return m_sizeY;
}

double TsunamiManagerInfo::TsunamiData::startX() const
{
    return m_startX;
}

double TsunamiManagerInfo::TsunamiData::startY() const
{
    return m_startY;
}

double TsunamiManagerInfo::TsunamiData::endX() const
{
    return m_endX;
}

double TsunamiManagerInfo::TsunamiData::endY() const
{
    return m_endY;
}

double TsunamiManagerInfo::TsunamiData::stepX() const
{
    return m_stepX;
}

double TsunamiManagerInfo::TsunamiData::stepY() const
{
    return m_stepY;
}

QString TsunamiManagerInfo::TsunamiData::bathymetryPath() const
{
    return m_bathymetryPath;
}

QString TsunamiManagerInfo::TsunamiData::brickPath() const
{
    return m_brickPath;
}

QString TsunamiManagerInfo::TsunamiData::imageSavePath() const
{
    return m_imageSavePath;
}

QString TsunamiManagerInfo::TsunamiData::maxDistributionSavePath() const
{
    return m_maxDistributionSavePath;
}

void TsunamiManagerInfo::TsunamiData::setSizeX(uint size) {
    if (m_sizeX != size) {
        m_sizeX = size;
        emit sizeXChanged(size);
    }
}

void TsunamiManagerInfo::TsunamiData::setSizeY(uint size) {
    if (m_sizeY != size) {
        m_sizeY = size;
        emit sizeYChanged(size);
    }
}

void TsunamiManagerInfo::TsunamiData::setStartX(double start) {
    if (m_startX != start) {
        m_startX = start;
        emit startXChanged(start);
    }
}

void TsunamiManagerInfo::TsunamiData::setStartY(double start) {
    if (m_startY != start) {
        m_startY = start;
        emit startYChanged(start);
    }
}

void TsunamiManagerInfo::TsunamiData::setEndX(double end) {
    if (m_endX != end) {
        m_endX = end;
        emit endXChanged(end);
    }
}

void TsunamiManagerInfo::TsunamiData::setEndY(double end) {
    if (m_endY != end) {
        m_endY = end;
        emit endYChanged(end);
    }
}

void TsunamiManagerInfo::TsunamiData::setStepX(double step) {
    if (m_stepX != step) {
        m_stepX = step;
        emit stepXChanged(step);
    }
}

void TsunamiManagerInfo::TsunamiData::setStepY(double step) {
    if (m_stepY != step) {
        m_stepY = step;
        emit stepYChanged(step);
    }
}

void TsunamiManagerInfo::TsunamiData::setImageSavePath(QString imageSavePath)
{
    imageSavePath = imageSavePath.remove("file:///");
    if (m_imageSavePath == imageSavePath)
        return;

    m_imageSavePath = imageSavePath;
    emit imageSavePathChanged();
}

void TsunamiManagerInfo::TsunamiData::setMaxDistributionSavePath(QString maxDistributionSavePath)
{
    maxDistributionSavePath = maxDistributionSavePath.remove("file:///");
    if (m_maxDistributionSavePath == maxDistributionSavePath)
        return;

    m_maxDistributionSavePath = maxDistributionSavePath;
    emit maxDistributionSavePathChanged();
}

void TsunamiManagerInfo::TsunamiData::setBrickPath(const QString &brickPath)
{
    m_brickPath = brickPath;
    emit brickPathChanged();
}

void TsunamiManagerInfo::TsunamiData::setBathymetryPath(const QString &bathymetryPath)
{
    m_bathymetryPath = bathymetryPath;
    emit bathymetryPathChanged();
}
