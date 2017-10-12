#include "TsunamiManager/MapData.h"


TsunamiManagerInfo::MapData::MapData(QObject *parent) :
    QObject(parent)
{
}

TsunamiManagerInfo::MapData::~MapData() {}

uint TsunamiManagerInfo::MapData::sizeX() const
{
    return m_sizeX;
}

uint TsunamiManagerInfo::MapData::sizeY() const
{
    return m_sizeY;
}

double TsunamiManagerInfo::MapData::startX() const
{
    return m_startX;
}

double TsunamiManagerInfo::MapData::startY() const
{
    return m_startY;
}

double TsunamiManagerInfo::MapData::endX() const
{
    return m_endX;
}

double TsunamiManagerInfo::MapData::endY() const
{
    return m_endY;
}

double TsunamiManagerInfo::MapData::stepX() const
{
    return m_stepX;
}

double TsunamiManagerInfo::MapData::stepY() const
{
    return m_stepY;
}

void TsunamiManagerInfo::MapData::setSizeX(uint size) {
    if (m_sizeX != size) {
        m_sizeX = size;
        emit sizeXChanged(size);
    }
}

void TsunamiManagerInfo::MapData::setSizeY(uint size) {
    if (m_sizeY != size) {
        m_sizeY = size;
        emit sizeYChanged(size);
    }
}

void TsunamiManagerInfo::MapData::setStartX(double start) {
    if (m_startX != start) {
        m_startX = start;
        emit startXChanged(start);
    }
}

void TsunamiManagerInfo::MapData::setStartY(double start) {
    if (m_startY != start) {
        m_startY = start;
        emit startYChanged(start);
    }
}

void TsunamiManagerInfo::MapData::setEndX(double end) {
    if (m_endX != end) {
        m_endX = end;
        emit endXChanged(end);
    }
}

void TsunamiManagerInfo::MapData::setEndY(double end) {
    if (m_endY != end) {
        m_endY = end;
        emit endYChanged(end);
    }
}

void TsunamiManagerInfo::MapData::setStepX(double step) {
    if (m_stepX != step) {
        m_stepX = step;
        emit stepXChanged(step);
    }
}

void TsunamiManagerInfo::MapData::setStepY(double step) {
    if (m_stepY != step) {
        m_stepY = step;
        emit stepYChanged(step);
    }
}