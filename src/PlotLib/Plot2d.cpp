#include "PlotLib/Plot2d.h"
#include <QDebug>

namespace PlotLib{
Plot2d::Plot2d(QObject *parent, QImage* image) :
    QObject(parent),
    m_image(image)
{

}

Plot2d::~Plot2d()
{
    delete m_image;
}

void Plot2d::setWindow(QRect window) {

    if(m_window != window) {
        m_window = window;
    }

    if (m_image->size() == QSize(0, 0)) {
        m_painter.begin(m_image);
        m_painter.fillRect(window, QColor(255, 255, 255));
    }
    else m_painter.fillRect(window, QColor(255, 255, 255));
    m_windowA = window;

    if (m_colorbar) {
        m_window.setRect(window.x() + 85, window.y(), window.width() - 200, window.height() - 40 );
    }
    else {
        m_window.setRect(window.x() + 85, window.y(), window.width() - 150, window.height() - 40);
    }
}

void Plot2d::setRegion(QRectF region) {
    if(m_region != region) {
        m_region = region;
    }
}

void Plot2d::setAxisX(bool draw) {
    if(m_axisX != draw) {
        m_axisX = draw;
    }
}

void Plot2d::setAxisY(bool draw) {
    if(m_axisY != draw) {
        m_axisY = draw;
    }
}

void Plot2d::setColorbar(bool draw) {
    if(m_colorbar != draw) {
        m_colorbar = draw;
    }
}

void Plot2d::setImage(QImage *image)
{
    if (image != m_image) {
        m_image = image;
    }
}

QRect Plot2d::window() {
    return m_window;
}

QRectF Plot2d::region() {
    return m_region;
}

bool Plot2d::axisX() {
    return m_axisX;
}

bool Plot2d::axisY() {
    return m_axisY;
}

bool Plot2d::colorbar()
{
    return m_colorbar;
}

void Plot2d::plotColorFunction(colorFunc2D &f, QRectF region)
{
    QPoint a = getPoint(QPointF(region.x(), region.y()));
    QPoint b = getPoint(QPointF(region.x() + region.width(), region.y() + region.height()));
    QRect r;
    r.setX(std::min(a.x(), b.x()));
    r.setY(std::min(a.y(), b.y()));
    r.setWidth(std::abs(b.x() - a.x()));
    r.setHeight(std::abs(b.y() - a.y()));
    for (int x = 0; x < r.width(); x++) {
        for (int y = 0; y < r.height(); y++) {
            QPointF pt = getRealPoint(QPoint(x + a.x(), y + b.y()));
            QColor col = f(pt.x(), pt.y());
            m_image->setPixelColor(x, y, col);
        }
    }
}

void Plot2d::plotColorFunction(colorFunc2D &f)
{
    plotColorFunction(f, m_region);
}

QPointF Plot2d::getStep()
{
    QRect r;
    QRectF region = m_region;
    QPoint a = getPoint(QPointF(region.x(), region.y()));
    QPoint b = getPoint(QPointF(region.x() + region.width(), region.y() + region.height()));

    r.setX(std::min(a.x(), b.x()));
    r.setY(std::min(a.y(), b.y()));
    r.setWidth(std::abs(b.x() - a.x()));
    r.setHeight(std::abs(b.y() - a.y()));
    QPointF pt = getRealPoint(QPoint(0 + a.x(), 0 + b.y()));
    QPointF pt1 = getRealPoint(QPoint(1 + a.x(), 1 + b.y()));
    return QPointF(pt1.x() - pt.x(), pt1.y() - pt.y());
}

QPointF Plot2d::getRealPoint(QPoint point)
{
    QPointF answer;
    answer.setX(m_region.width() *
                ((double)point.x() - m_window.x()) /
                m_window.width() + m_region.x());

    answer.setY(m_region.height() *
                ((double)m_window.y() + m_window.height() - point.y()) /
                m_window.height() + m_region.y());
    return answer;
}

QPoint Plot2d::getPoint(const QPointF point)
{
    QPoint answer;

    answer.setX((int)(m_window.x() + m_window.width() *
                      (point.x() - m_region.x()) / m_region.width()));
    answer.setY((int)(m_window.y() + m_window.height() - m_window.height() *
                      (point.y() - m_region.y()) / m_region.height()));

    return answer;
}
}
