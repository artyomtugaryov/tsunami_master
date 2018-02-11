#ifndef COLORMAP_H
#define COLORMAP_H

#include <QObject>
#include <QColor>
#include <functional>
#include <map>


namespace PlotLib {


QColor operator * (QColor x, double y);
QColor operator + (QColor x, QColor y);

template <typename T> using funcColorMap = std::function <QColor(T val)>;

class ColorMap : public QObject {
    Q_OBJECT
public:
    ColorMap(QObject *parent = nullptr);
    ColorMap(std::map <double, QColor> map, bool interpalation = true, QObject *parent = nullptr);

    ColorMap(funcColorMap<double> funcColor, QObject *parent = nullptr);
    QColor getColor(double val) { return m_funcColor(val); }

    double min() const;
    double max() const;
    void resetColorMap(std::map<double, QColor> map);
//    void setColorIntervalByIndex(QColor color, double interval, double oldInterval);
public slots:

signals:

private:
    std::map <double, QColor> m_mapColor;
    bool m_interpolation;
    funcColorMap<double> m_funcColor{ ([this](double val) -> QColor { // linear interpolation
            auto it = m_mapColor.lower_bound(val);
            if (it == m_mapColor.end()) {
                return prev(it)->second;
            }
            else if (it == m_mapColor.begin()) {
                return it->second;
            }
            else {
                double al = ((val - prev(it)->first) / (it->first - prev(it)->first));
                return (prev(it)->second) * (1.0 - al) + (it->second) * al;
            }
        })};
};
}
#endif //COLORMAP_H
