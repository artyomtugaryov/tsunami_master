#include "PlotLib/ColorMap.h"
#include <cassert>

namespace  PlotLib {

ColorMap::ColorMap(QObject *parent) :
    QObject(parent)
{

}

ColorMap::ColorMap(std::map <double, QColor> map, bool interpalation, QObject *parent) :
    QObject(parent),
    m_mapColor(map),
    m_interpolation(interpalation)
{
    assert(map.size());
}

ColorMap::ColorMap(funcColorMap<double> funcColor, QObject *parent) :
    QObject(parent),
    m_funcColor(funcColor)
{

}

double ColorMap::min() const{
    return m_mapColor.begin()->first;
}

double ColorMap::max() const  {
    return m_mapColor.rbegin()->first;
}

void ColorMap::resetColorMap(std::map <double, QColor> map)
{
    m_mapColor.clear();
    m_mapColor = map;
}

//void ColorMap::setColorIntervalByIndex(QColor color, double interval, double oldInterval)
//{
//    if (m_mapColor.size() >= index)
//    {
//        m_mapColor.[index];// = {interval, color};
//    }
//    else
//    {
//        qWarning() << "Out of range";
//    }
//}

QColor operator * (QColor x, double y)
{
    return QColor{ static_cast<int>(x.red() * y), static_cast<int>(x.green() * y), static_cast<int>(x.blue() * y) };
}

QColor operator + (QColor x, QColor y)
{
    return QColor((unsigned int)(x.red() + y.red()), (unsigned int)(x.green() + y.green()), (unsigned int)(x.blue() + y.blue()));
}
}
