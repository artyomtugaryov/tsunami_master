#include "TMlib/TMBrickPoint.h"

TM::Focus::BrickPoint::BrickPoint(double x, double y) : m_x(x), m_y(y) {}

bool TM::Focus::BrickPoint::operator<(const BrickPoint &other) const noexcept{
    return m_x < other.m_x;
}

double TM::Focus::BrickPoint::x() const {
    return m_x;
}

double TM::Focus::BrickPoint::y() const {
    return m_y;
}
double TM::Focus::BrickPoint::rotate(const BrickPoint &a, const BrickPoint &b, const BrickPoint &c) {
    return (b.m_x - a.m_x) * (c.m_y - b.m_y) - (b.m_y - a.m_y) * (c.m_x - b.m_x);
}

bool TM::Focus::BrickPoint::intersect(const BrickPoint &a, const BrickPoint &b, const BrickPoint &c, const BrickPoint &d) {
    return ((BrickPoint::rotate(a, b, c) * BrickPoint::rotate(a, b, d)) <= 0) && ((BrickPoint::rotate(c, d, a) * BrickPoint::rotate(c, d, b)) < 0);
}