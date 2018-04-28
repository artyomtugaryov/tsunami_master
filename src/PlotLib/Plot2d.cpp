#include "PlotLib/Plot2d.h"
#include <QDebug>

namespace PlotLib {
//TODO: use const?
#define WIDTH_CHAR 12
//TODO: use const?
#define FONT_FAMILY "Times New Roman"

Plot2d::Plot2d(QObject *parent, QImage* image) :
    QObject(parent),
    m_image(image)
{

}

void Plot2d::setWindow(QRect window) {

    if(m_window != window) {
        m_window = window;
    }

    if (!m_painter.isActive()) {
        m_painter.begin(m_image);
    }

    m_painter.fillRect(window, QColor(255, 255, 255));
    m_windowA = window;
    if (m_colorbar) {
        m_window.setRect(window.x() + 85, window.y(), window.width() - 200, window.height() - 40 );
    }
    else {
        m_window.setRect(window.x() + 85, window.y(), window.width() - 150, window.height() - 40);
    }
    m_painter.end();
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

void Plot2d::drawAxis(int fontSize)
{
    if(m_image == nullptr) {
        return;
    }

    if (!m_painter.isActive()) {
        m_painter.begin(m_image);
    }

    m_painter.setFont(QFont(FONT_FAMILY, fontSize, QFont::Bold));

    if(m_axisX) {
        QPoint a = getPoint(QPointF(m_region.x(), m_region.y()));
        QPoint b = getPoint(QPointF(m_region.x() + m_region.width(), m_region.y()));
        m_painter.drawLine(a, b);
    }

    if(m_axisY) {
        QPoint a = getPoint(QPointF(m_region.x(), m_region.y()));
        QPoint b = getPoint(QPointF(m_region.x(), m_region.y() + m_region.height()));
        m_painter.drawLine(a, b);
    }

    if (m_axisX && m_axisY) {
        QPoint pointY = QPoint(m_window.x() - 35, m_window.y() + 50);
        m_painter.drawText(pointY, m_axisLabelY);
        if (m_colorbar){
            QPoint pointX  = QPoint(static_cast<int>(m_window.x() + m_window.width() +
                                                     35 - WIDTH_CHAR * static_cast<int>(m_axisLabelX.size())),
                                    static_cast<int>(m_window.y() + m_window.height()));
            m_painter.drawText(pointX, m_axisLabelX);
        }
        else {
            QPoint pointX  = QPoint(static_cast<int>(m_window.x() + m_window.width() -
                                                     WIDTH_CHAR * static_cast<int>(m_axisLabelX.size()) + 35),
                                    static_cast<int>(m_window.y() + m_window.height()) - 30);
            m_painter.drawText(pointX, m_axisLabelX);
        }
    }
    m_painter.end();
}

void Plot2d::drawGrid(bool grid, int fontSize, double stepX,
                      double stepY, double stepFontX, double stepFontY)
{
    if (!m_painter.isActive()) {
        m_painter.begin(m_image);
    }
    m_painter.setFont(QFont(FONT_FAMILY, fontSize, QFont::Bold));
    int k = (int)trunc(log(m_region.width()) / log(m_axis_x_base));
    double dx = exp(log(m_axis_x_base) * k), dxFont = dx;
    int maxK = m_window.width() / (WIDTH_CHAR * (k + 7));
    if (stepX > 0.001) {
        dx = stepX;
    }
    else {
        while (m_region.width() < maxK * dx / 10) {
            dx /= 10, k--;
        }
        if (m_region.width() < maxK * dx / 5) {
            dx /= 5, k--;
        }
        if (m_region.width() < maxK * dx / 2) {
            dx /= 2, k--;
        }
    }

    for (double x = round(m_region.x() / dx + 0.5) * dx; x < m_region.width() + m_region.x() + dx / 10.0; x += dx) {
        if (abs(x) < dx / 100) x = 0;
        QPoint a = getPoint(QPointF(x, m_region.y()));
        if (grid) m_painter.drawLine(a, getPoint(QPointF(x, m_region.height() + m_region.y())));
        m_painter.drawLine(a + QPoint(-1, -5), a + QPoint(-1, 5));
        m_painter.drawLine(a + QPoint(0, -5), a + QPoint(0, 5));
        m_painter.drawLine(a + QPoint(1, -5), a + QPoint(1, 5));
    }
    if (stepFontX > 0.01) dxFont = stepFontX;
    else dxFont = dx;
    for (double x = round(m_region.x() / dxFont + 0.5) * dxFont;
         x < m_region.width() + m_region.x() + dxFont / 10.0; x += dxFont) {
        QString value = QString::number(x);
        double marginX =  -WIDTH_CHAR * (int)value.size() / 2 * 3 + 20;
        QPoint a = getPoint(QPointF(x, m_region.y()));
        m_painter.drawText(a + QPoint(marginX, 35), value);
        m_painter.drawLine(a + QPoint(-2,0), a + QPoint(-2, 5));
        m_painter.drawLine(a + QPoint(2,0), a + QPoint(2, 5));
    }

    k = static_cast<int>(trunc(log(m_region.height()) / log(m_axis_y_base)));
    double dy = exp(log(m_axis_y_base) * k), dyFont = dy;
    if (stepY > 0.001) dy = stepY;
    maxK = m_window.height() / 30;

    while (m_region.height() < maxK * dy / 10) {
        dy /= 10, k--;
    }
    if (m_region.height() < maxK * dy / 5) {
        dy /= 5, k--;
    }
    if (m_region.height() < maxK * dy / 2) {
        dy /= 2, k--;
    }
    for (double y = round(m_region.y() / dy + 0.5) * dy;
         y < m_region.height() + m_region.y() + dy - 1 / m_axis_y_base; y += dy) {
        if (abs(y) < dy / 100) y = 0;
        QPoint a = getPoint(QPointF(m_region.x(), y));
        if (grid) m_painter.drawLine(a, getPoint(QPointF(m_region.x() + m_region.width(), y)));
        m_painter.drawLine(a + QPoint(-5, -1), a + QPoint(5, -1));
        m_painter.drawLine(a + QPoint(-5, 0), a + QPoint(5, 0));
        m_painter.drawLine(a + QPoint(-5, 1), a + QPoint(5, 1));
    }
    if (stepFontY > 0.01) dyFont = stepFontY;
    else dyFont = dy;
    for (double y = round(m_region.y() / dy + 0.5) * dyFont;
         y < m_region.height() + m_region.y() + dyFont / m_axis_y_base - 1; y += dyFont) {
        QString value = QString::number(y);
        QPoint a = getPoint(QPointF(m_region.x(), y));
        double marginX = static_cast<int>(-WIDTH_CHAR * (static_cast<double>(value.size() + 1.7)));
        double marginY = -WIDTH_CHAR + 25;
        m_painter.drawText(a + QPoint(marginX, marginY), value);
        m_painter.drawLine(a + QPoint(-5, -2), a + QPoint(0, -2));
        m_painter.drawLine(a + QPoint(-5, 2), a + QPoint(0, 2));
    }
    m_painter.end();
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
    for (int x = 0; x <= r.width(); x++) {
        for (int y = 0; y <= r.height(); y++) {
            QPointF pt = getRealPoint(QPoint(x + a.x(), y + b.y()));
            QColor col = f(pt.x(), pt.y());
            m_image->setPixelColor(x + m_window.x(), y, col);
        }
    }
}

void Plot2d::plotColorFunction(colorFunc2D &f)
{
    plotColorFunction(f, m_region);
}

void Plot2d::drawColorbar(ColorMap &colorMap, std::vector<double> ticks, int fontSize)
{
    if (!m_painter.isActive()) {
        m_painter.begin(m_image);
    }
    m_painter.setFont(QFont(FONT_FAMILY, fontSize, QFont::Bold));
    double a = colorMap.min(), b = colorMap.max();
    int ay = m_window.y(), by = m_window.y() + m_window.height();
    int w = 35, cx = m_windowA.width() - 95;

    for (int y = ay; y < by; y++) {
        QColor color = colorMap.getColor((b - a) * y / ((double)ay - by) + b);
        m_painter.setPen(color);
        m_painter.drawLine(QPoint(cx, y), QPoint(cx + w - 1, y));
    }
    m_painter.setPen(QColor(0, 0, 0));
    for (auto x : ticks)
    {
        QPoint p = QPoint(cx + w + 5, static_cast<int>((ay - by) *(x - a) / (b - a) + by));
        if (x == ticks[ticks.size() - 1]) {
            m_painter.drawText( p + QPoint(0, -WIDTH_CHAR - 10), "(m)");
        }
        m_painter.drawText(p + QPoint(0, - WIDTH_CHAR - 5  + 25), QString::number(x));
        m_painter.drawLine(p + QPoint(-w - 5, 0), p + QPoint(-5, 0));
    }
    m_painter.drawLine(QPoint(cx, ay), QPoint(cx + w, ay));
    m_painter.drawLine(QPoint(cx, by - ay), QPoint(cx, ay));
    m_painter.drawLine(QPoint(cx + w, by - ay), QPoint(cx + w, ay));
    m_painter.drawLine(QPoint(cx, by - ay), QPoint(cx + w, by - ay));
    m_painter.end();
}

void Plot2d::drawPointByIndex(double x, double y)
{
    if (!m_painter.isActive()) {
        m_painter.begin(m_image);
    }
    QPoint a = getPoint(QPointF(x, y));
    m_painter.setBrush(Qt::red);
    m_painter.drawEllipse(a, 10, 10);
    m_painter.setBrush(Qt::blue);
    m_painter.drawEllipse(a, 5, 5);
    m_painter.end();
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

QString Plot2d::getAxisLabelX() const
{
    return m_axisLabelX;
}

void Plot2d::setAxisLabelX(const QString &label)
{
    if (m_axisLabelX != label) {
        m_axisLabelX = label;
    }
}

QString Plot2d::getAxisLabelY() const
{
    return m_axisLabelY;
}

void Plot2d::setAxisLabelY(const QString &label)
{
    if (m_axisLabelY != label) {
        m_axisLabelY = label;
    }
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
