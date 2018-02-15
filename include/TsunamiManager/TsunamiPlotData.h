#ifndef TSUNAMIPLOTDATA_H
#define TSUNAMIPLOTDATA_H

#include <QObject>
#include <map>
#include <PlotLib/ColorMap.h>

namespace TsunamiManagerInfo {
class TsunamiPlotData : public QObject
{

    Q_OBJECT

    Q_PROPERTY(uint width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(uint height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(uint fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
    Q_PROPERTY(uint colorBarFontSize READ colorBarFontSize WRITE setColorBarFontSize
               NOTIFY colorBarFontSizeChanged)

    Q_PROPERTY(int offsetX READ offsetX WRITE setOffsetX NOTIFY offsetXChanged)
    Q_PROPERTY(int offsetY READ offsetY WRITE setOffsetY NOTIFY offsetYChanged)

    Q_PROPERTY(int offsetLabelX READ offsetLabelX WRITE setOffsetLabelX
               NOTIFY offsetLabelXChanged)
    Q_PROPERTY(int offsetLabelY READ offsetLabelY WRITE setOffsetLabelY
               NOTIFY offsetLabelYChanged)

    Q_PROPERTY(uint stepX READ stepX WRITE setStepX NOTIFY stepXChanged)
    Q_PROPERTY(uint stepY READ stepY WRITE setStepY NOTIFY stepYChanged)
    Q_PROPERTY(uint stepColorBar READ stepColorBar WRITE setStepColorBar
               NOTIFY stepColorBarChanged)

    Q_PROPERTY(bool isColorBarIntervalsAreCorrect
               READ isColorBarIntervalsAreCorrect
               WRITE setIsColorBarIntervalsAreCorrect
               NOTIFY isColorBarIntervalsAreCorrectChanged)


    Q_PROPERTY(QList <QString> colors READ colors CONSTANT)
    Q_PROPERTY(QList <double> colorBarIntervals READ colorBarIntervals CONSTANT)

public:
    TsunamiPlotData(QObject *parent = 0);
    virtual ~TsunamiPlotData();

    uint width() const;

    uint height() const;

    uint fontSize() const;

    uint colorBarFontSize() const;

    int offsetX() const;

    int offsetY() const;

    int offsetLabelX() const;

    int offsetLabelY() const;

    uint stepX() const;

    uint stepY() const;

    uint stepColorBar() const;

    bool isColorBarIntervalsAreCorrect() const;

    QList <double> colorBarIntervals() const;

    QList <QString> colors() const;

   // PlotLib::ColorMap colorBarMap() const;

public slots:
    void setWidth(uint width);
    void setHeight(uint height);
    void setFontSize(uint fontSize);
    void setColorBarFontSize(uint colorBarFontSize);

    void setOffsetX(int offsetX);
    void setOffsetY(int offsetY);
    void setOffsetLabelX(int offsetLabelX);
    void setOffsetLabelY(int offsetLabelY);

    void setStepX(uint stepX);
    void setStepY(uint stepY);
    void setStepColorBar(uint stepColorBar);

    void setIsColorBarIntervalsAreCorrect(bool isColorBarIntervalsAreCorrect);

    void setColorIntervalByIndex(QColor color, double interval, uint index);
signals:


    void widthChanged(uint width);

    void heightChanged(uint height);

    void fontSizeChanged(uint fontSize);

    void colorBarFontSizeChanged(uint colorBarFontSize);

    void offsetXChanged(int offsetX);

    void offsetYChanged(int offsetY);

    void offsetLabelXChanged(int offsetLabelX);

    void offsetLabelYChanged(int offsetLabelY);

    void stepXChanged(uint stepX);

    void stepYChanged(uint stepY);

    void stepColorBarChanged(uint stepColorBar);

    void isColorBarIntervalsAreCorrectChanged(bool isColorBarIntervalsAreCorrect);

private:

    void setColorBarMap();

    uint m_width;
    uint m_height;
    uint m_fontSize;
    uint m_colorBarFontSize;
    int m_offsetX;
    int m_offsetY;
    int m_offsetLabelX;
    int m_offsetLabelY;
    uint m_stepX;
    uint m_stepY;
    uint m_stepColorBar;
    bool m_isColorBarIntervalsAreCorrect;
    PlotLib::ColorMap m_colorBarMap;
    QList <double> m_colorBarIntervals;
    QList <QString> m_colors;
};
}
#endif // TSUNAMIPLOTDATA_H
