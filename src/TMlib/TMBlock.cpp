#include <algorithm>

#include "TMlib/TMBlock.h"
#include "TMlib/TMException.h"

bool TM::Focus::Block::has(const double &lat, const double &lon) {
    return pointLocation({lat, lon});
}

double TM::Focus::Block::getUpHeight(const double &t) {
    for (auto brickUp : m_numberUp) {
        if (this->m_beginT > t or t > this->m_beginT + brickUp.get_brickUpT()) {
            return 0;
        } else {
            return brickUp.get_heightUp() / brickUp.get_brickUpT() * t;
        }
    }
    return 0;
}

bool TM::Focus::Block::pointLocation(const BrickPoint &a) {
    auto n = m_points.size();
    if (BrickPoint::rotate(m_points[0], m_points[1], a) < 0 || BrickPoint::rotate(m_points[0], m_points[n - 1], a) > 0)
        return false;
    auto p = 1;
    auto r = n - 1;
    while (r - p > 1) {
        auto q = (p + r) / 2;
        if (BrickPoint::rotate(m_points[0], m_points[q], a) < 0) {
            r = q;
        } else {
            p = q;
        }
    }
    return !BrickPoint::intersect(m_points[0], a, m_points[p], m_points[r]);
}

void TM::Focus::Block::buildBlock(std::vector<TM::Focus::BrickPoint> &points) {
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
    if (points[*p.begin()].y() > points[*(p.end()-1)].y()){
        std::reverse(std::begin(p), std::end(p));
    }
    for (size_t i(0); i < n; i++) {
        m_points[i] = points[p[i]];
    }
}

double& TM::Focus::Block::get_beginT(){
    return m_beginT;
}

std::vector<TM::Focus::BrickPoint>& TM::Focus::Block::get_points() {
    return m_points;
}

std::vector<TM::Focus::BrickUp>& TM::Focus::Block::get_numberUp() {
    return m_numberUp;
}
