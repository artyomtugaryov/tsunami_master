#include "TMlib/TMBlock.h"

bool TM::TMBlock::has(double lat, double lon) {
    return pointloc({lat, lon});
}

double TM::TMBlock::getUpHeihgt(double t) {
    for (auto brickUp = this->m_numberUp.begin(); brickUp != m_numberUp.end(); brickUp++) {
        if (this->m_beginT > t or t > this->m_beginT + brickUp->m_brickUpT) {
            return 0;
        } else {
            auto speed = static_cast<double>(brickUp->m_brickUpT) / brickUp->m_heightUp;
            return speed * t;
        }
    }
}

bool TM::TMBlock::pointloc(const TMBrickPoint &a) {
    std::size_t n = m_points.size();
    if (rotate(m_points[0], m_points[1], a) < 0 || rotate(m_points[0], m_points[n - 1], a) > 0)
        return false;
    std::size_t p = 1, r = n - 1;
    while (r - p > 1) {
        std::size_t q = (p + r) / 2; //maybe double?
        if (rotate(m_points[0], m_points[q], a) < 0) {
            r = q;
        } else {
            p = q;
        }
    }
    return !intersect(m_points[0], a, m_points[p], m_points[r]);
}