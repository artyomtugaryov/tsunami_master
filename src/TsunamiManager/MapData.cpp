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

double TsunamiManagerInfo::MapData::deltaX() const
{
    return m_deltaX;
}

double TsunamiManagerInfo::MapData::deltaY() const
{
    return m_deltaY;
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

void TsunamiManagerInfo::MapData::setDeltaX(double delta) {
    if (m_deltaX != delta) {
        m_deltaX = delta;
        emit deltaXChanged(delta);
    }
}

void TsunamiManagerInfo::MapData::setDeltaY(double delta) {
    if (m_deltaY != delta) {
        m_deltaY = delta;
        emit deltaYChanged(delta);
    }
}
