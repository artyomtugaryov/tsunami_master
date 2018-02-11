#include "TsunamiManager/TsunamiPlotData.h"

#include <QDebug>

using namespace TsunamiManagerInfo;

TsunamiPlotData::TsunamiPlotData(QObject *parent) :
    QObject(parent),
    m_width(0),
    m_height(0),
    m_fontSize(0),
    m_colorBarFontSize(0),
    m_offsetX(0),
    m_offsetY(0),
    m_offsetLabelX(0),
    m_offsetLabelY(0),
    m_stepX(0),
    m_stepY(0),
    m_stepColorBar(0),
    m_isColorBarIntervalsAreCorrect(true),
    m_colorBarMap({{-3, QColor(38, 0, 255)},
{-0.1, QColor(222, 255, 248)},
{0, QColor(222, 255, 248)},
{1, QColor(128, 0, 128)},
{3, QColor(255, 0, 0)},
{5, QColor(255, 128, 0)},
{8, QColor(255, 255, 0)},
{11, QColor(0, 255, 0 )}})
{
    m_colorBarIntervals << -3 << 0 << 1 << 3 << 5 << 8 << 11;
    m_colorBar << QColor(38, 0, 255) << QColor(222, 255, 248) << QColor(128, 0, 128)
                                     << QColor(255, 0, 0) << QColor(255, 128, 0)
                                     << QColor(255, 255, 0) << QColor(0, 255, 0 );
    //qDebug() << m_colorBar;
    setColorBarMap();
}

uint TsunamiPlotData::width() const
{
    return m_width;
}

uint TsunamiPlotData::height() const
{
    return m_height;
}

uint TsunamiPlotData::fontSize() const
{
    return m_fontSize;
}

uint TsunamiPlotData::colorBarFontSize() const
{
    return m_colorBarFontSize;
}

int TsunamiPlotData::offsetX() const
{
    return m_offsetX;
}

int TsunamiPlotData::offsetY() const
{
    return m_offsetY;
}

int TsunamiPlotData::offsetLabelX() const
{
    return m_offsetLabelX;
}

int TsunamiPlotData::offsetLabelY() const
{
    return m_offsetLabelY;
}

uint TsunamiPlotData::stepX() const
{
    return m_stepX;
}

uint TsunamiPlotData::stepY() const
{
    return m_stepY;
}

uint TsunamiPlotData::stepColorBar() const
{
    return m_stepColorBar;
}

bool TsunamiPlotData::isColorBarIntervalsAreCorrect() const
{
    return m_isColorBarIntervalsAreCorrect;
}

QList<QColor> TsunamiPlotData::colorBar() const
{
    return m_colorBar;
}

QList<double> TsunamiPlotData::colorBarIntervals() const
{
    return m_colorBarIntervals;
}

void TsunamiPlotData::setWidth(uint width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged(width);
}

void TsunamiPlotData::setHeight(uint height)
{
    if (m_height == height)
        return;

    m_height = height;
    emit heightChanged(height);
}

void TsunamiPlotData::setFontSize(uint fontSize)
{
    if (m_fontSize == fontSize)
        return;

    m_fontSize = fontSize;
    emit fontSizeChanged(fontSize);
}

void TsunamiPlotData::setColorBarFontSize(uint colorBarFontSize)
{
    if (m_colorBarFontSize == colorBarFontSize)
        return;

    m_colorBarFontSize = colorBarFontSize;
    emit colorBarFontSizeChanged(colorBarFontSize);
}

void TsunamiPlotData::setOffsetX(int offsetX)
{
    if (m_offsetX == offsetX)
        return;

    m_offsetX = offsetX;
    emit offsetXChanged(offsetX);
}

void TsunamiPlotData::setOffsetY(int offsetY)
{
    if (m_offsetY == offsetY)
        return;

    m_offsetY = offsetY;
    emit offsetYChanged(offsetY);
}

void TsunamiPlotData::setOffsetLabelX(int offsetLabelX)
{
    if (m_offsetLabelX == offsetLabelX)
        return;

    m_offsetLabelX = offsetLabelX;
    emit offsetLabelXChanged(offsetLabelX);
}

void TsunamiPlotData::setOffsetLabelY(int offsetLabelY)
{
    if (m_offsetLabelY == offsetLabelY)
        return;

    m_offsetLabelY = offsetLabelY;
    emit offsetLabelYChanged(offsetLabelY);
}

void TsunamiPlotData::setStepX(uint stepX)
{
    if (m_stepX == stepX)
        return;

    m_stepX = stepX;
    emit stepXChanged(stepX);
}

void TsunamiPlotData::setStepY(uint stepY)
{
    if (m_stepY == stepY)
        return;

    m_stepY = stepY;
    emit stepYChanged(stepY);
}

void TsunamiPlotData::setStepColorBar(uint stepColorBar)
{
    if (m_stepColorBar == stepColorBar)
        return;

    m_stepColorBar = stepColorBar;
    emit stepColorBarChanged(stepColorBar);
}

void TsunamiPlotData::setIsColorBarIntervalsAreCorrect(bool isColorBarIntervalsAreCorrect)
{
    if (m_isColorBarIntervalsAreCorrect == isColorBarIntervalsAreCorrect)
        return;

    m_isColorBarIntervalsAreCorrect = isColorBarIntervalsAreCorrect;
    emit isColorBarIntervalsAreCorrectChanged(isColorBarIntervalsAreCorrect);
}

void TsunamiPlotData::setColorIntervalByIndex(QColor color, double interval, uint index)
{
    Q_UNUSED(color)
    Q_UNUSED(interval)
    Q_UNUSED(index)


}

void TsunamiPlotData::setColorBarMap()
{
    qDebug() << "OOOOOOOOOOOOOOOOOO";
//    m_colorBarMap.resetColorMap({{m_colorBarIntervals[0], m_colorBar[0]},
//                              {-0.01, m_colorBar[1]},
//                              {m_colorBarIntervals[1], m_colorBar[1]},
//                              {m_colorBarIntervals[2], m_colorBar[2]},
//                              {m_colorBarIntervals[3], m_colorBar[3]},
//                              {m_colorBarIntervals[4], m_colorBar[4]},
//                              {m_colorBarIntervals[5], m_colorBar[5]},
//                              {m_colorBarIntervals[6], m_colorBar[6]}});
    qDebug() << "BBBBBBBBBBBBBBBBBB";
}

TsunamiPlotData::~TsunamiPlotData() {}

