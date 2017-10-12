#ifndef PLOT2D_H
#define PLOT2D_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <functional>

typedef std::function <QColor(double, double)> colorFunc2D;

namespace PlotLib {
class Plot2d : public QObject
{

    Q_OBJECT
public:
    Plot2d(QObject *parent = 0, QImage* image = nullptr);
    virtual ~Plot2d();
    void resize();
    void setWindow(QRect window);
    void setRegion(QRectF region);
    void setAxisX(bool draw);
    void setAxisY(bool draw);
    void setColorbar(bool draw);
    void setImage(QImage *image);
    void setAxisLabelX(const QString &label);
    void setAxisLabelY(const QString &label);

    QRect window();
    QRectF region();
    bool axisX();
    bool axisY();
    bool colorbar();

    void drawAxis();
    void drawGrid(bool grid = true, bool ticks = true, unsigned int fontSize = 20,
                  double stepX = 0, double stepY = 0,
                  double stepFontX = 0, double stepFontY = 0);
    void drawText(QPointF point, QString text);
    void plotColorFunction(colorFunc2D & f, QRectF region);
    void plotColorFunction(colorFunc2D & f);

    QPointF getStep();
    QPoint getPoint(const QPointF point);
    QPointF getRealPoint(QPoint point);
    QString getAxisLabelX() const;
    QString getAxisLabelY() const;

signals:
private:
    QImage* m_image;
    QPainter m_painter;
    QRect m_window;
    QRect m_windowA;
    QRectF m_region;
    bool m_axisX {true}, m_axisY{true};
    double axis_x_base_ = 10.0, axis_y_base_ = 10.0;//Check
    QString m_axisLabelX, m_axisLabelY;
    bool m_colorbar{false};
};
}
#endif // PLOT2D_H
