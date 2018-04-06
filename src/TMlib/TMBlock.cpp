#include "TMlib/TMBlock.h"

bool TM::Focus::Block::has(double lat, double lon) {
    return pointLocation({lat, lon});
}

double TM::Focus::Block::getUpHeight(double t) {
    for (auto brickUp : m_numberUp) {
        if (this->m_beginT > t or t > this->m_beginT + brickUp.m_brickUpT) {
            return 0;
        } else {
            auto speed = (brickUp.m_heightUp) / brickUp.m_brickUpT;
            return speed * t;
        }
    }
}

bool TM::Focus::Block::pointLocation(const BrickPoint &a) {
    std::size_t n = m_points.size();
    if (BrickPoint::rotate(m_points[0], m_points[1], a) < 0 || BrickPoint::rotate(m_points[0], m_points[n - 1], a) > 0)
        return false;
    std::size_t p = 1, r = n - 1;
    while (r - p > 1) {
        std::size_t q = (p + r) / 2;
        if (BrickPoint::rotate(m_points[0], m_points[q], a) < 0) {
            r = q;
        } else {
            p = q;
        }
    }
    return !BrickPoint::intersect(m_points[0], a, m_points[p], m_points[r]);
}

double TM::Focus::BrickPoint::rotate(const BrickPoint &a, const BrickPoint &b, const BrickPoint &c) {
    return (b.m_x - a.m_x) * (c.m_y - b.m_y) - (b.m_y - a.m_y) * (c.m_x - b.m_x);
}

bool TM::Focus::BrickPoint::intersect(const BrickPoint &a, const BrickPoint &b, const BrickPoint &c, const BrickPoint &d) {
    return ((BrickPoint::rotate(a, b, c) * BrickPoint::rotate(a, b, d)) <= 0) && ((BrickPoint::rotate(c, d, a) * BrickPoint::rotate(c, d, b)) < 0);
}

void TM::Focus::Block::buildBlock(std::vector<TM::Focus::BrickPoint> points) {
    auto n = points.size();
    std::sort(points.begin(), points.end());
    std::vector<size_t> p(n);
    for (size_t i(0); i < n; i++) {
        p[i] = i;
    }
    for (size_t i(2); i < n; i++) {
        size_t j = i;
        while (j > 1 and BrickPoint::rotate(points[p[0]], points[p[j - 1]], points[p[j]]) < 0) {
            size_t tmp = p[j];
            p[j] = p[j - 1];
            p[j - 1] = tmp;
            j--;
        }
    }
    m_points.resize(n);
    if (points[*p.begin()].m_y > points[*(p.end()-1)].m_y){
        std::reverse(std::begin(p), std::end(p));
    }
    for (size_t i(0); i < n; i++) {
        m_points[i] = points[p[i]];
    }
}