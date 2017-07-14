#include "MapData.h"


MapData::MapData(QObject *parent) {
    Q_UNUSED(parent);
}

MapData::~MapData() {}

uint MapData::sizeX() const
{
    return m_sizeX;
}

uint MapData::sizeY() const
{
    return m_sizeY;
}

double MapData::startX() const
{
    return m_startX;
}

double MapData::startY() const
{
    return m_startY;
}

double MapData::endX() const
{
    return m_endX;
}

double MapData::endY() const
{
    return m_endY;
}

double MapData::deltaX() const
{
    return m_deltaX;
}

double MapData::deltaY() const
{
    return m_deltaY;
}

void MapData::setSizeX(uint size) {
    if (m_sizeX != size) {
        m_sizeX = size;
        emit sizeXChanged(size);
    }
}

void MapData::setSizeY(uint size) {
    if (m_sizeY != size) {
        m_sizeY = size;
        emit sizeYChanged(size);
    }
}

void MapData::setStartX(double start) {
    if (m_startX != start) {
        m_startX = start;
        emit startXChanged(start);
    }
}

void MapData::setStartY(double start) {
    if (m_startY != start) {
        m_startY = start;
        emit startYChanged(start);
    }
}

void MapData::setEndX(double end) {
    if (m_endX != end) {
        m_endX = end;
        emit endXChanged(end);
    }
}

void MapData::setEndY(double end) {
    if (m_endY != end) {
        m_endY = end;
        emit endYChanged(end);
    }
}

void MapData::setDeltaX(double delta) {
    if (m_deltaX != delta) {
        m_deltaX = delta;
        emit deltaXChanged(delta);
    }
}

void MapData::setDeltaY(double delta) {
    if (m_deltaY != delta) {
        m_deltaY = delta;
        emit deltaYChanged(delta);
    }
}
