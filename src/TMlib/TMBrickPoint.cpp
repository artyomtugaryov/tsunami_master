#include "TMlib/TMBrickPoint.h"

double TM::Focus::BrickPoint::rotate(const BrickPoint &a, const BrickPoint &b, const BrickPoint &c) {
    return (b.m_x - a.m_x) * (c.m_y - b.m_y) - (b.m_y - a.m_y) * (c.m_x - b.m_x);
}

bool TM::Focus::BrickPoint::intersect(const BrickPoint &a, const BrickPoint &b, const BrickPoint &c, const BrickPoint &d) {
    return ((BrickPoint::rotate(a, b, c) * BrickPoint::rotate(a, b, d)) <= 0) && ((BrickPoint::rotate(c, d, a) * BrickPoint::rotate(c, d, b)) < 0);
}
