#ifndef TSUNAMIMANAGER_TMBLOCK_H
#define TSUNAMIMANAGER_TMBLOCK_H

#include <vector>
#include <algorithm>

namespace TM {
    struct TMBrickPoint {
    public:
        double m_x;
        double m_y;

        TMBrickPoint(double x, double y) : m_x(x), m_y(y) {};
    };

    struct TMBrickUp {
    public:
        int m_brickUpT; // Time Up the block
        double m_heightUp; // Height Up the  block

        TMBrickUp(int b, double h) : m_brickUpT(b), m_heightUp(h) {};
    };

    struct TMBlock {

        bool has(double lat, double lon) {
            return pointloc({lat, lon});
        }

        double getUpHeihgt(double t) {
            for (auto brickUp = this->m_numberUp.begin(); brickUp != m_numberUp.end(); brickUp++) {
                if (t < this->m_beginT or t > this->m_beginT + brickUp->m_brickUpT) {
                    return 0;
                } else {
                    auto speed = static_cast<double>(brickUp->m_brickUpT) / brickUp->m_heightUp;
                    return speed * t;
                }
            }
        }

        bool pointloc(const TMBrickPoint &a) {
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

        static double rotate(const TMBrickPoint &a, const TMBrickPoint &b, const TMBrickPoint &c) {
            /*
             * https://habrahabr.ru/post/144571/
             * */
            return (b.m_x - a.m_x) * (c.m_y - b.m_y) - (b.m_y - a.m_y) * (c.m_x - b.m_x);
        }

        static bool
        intersect(const TMBrickPoint &a, const TMBrickPoint &b, const TMBrickPoint &c, const TMBrickPoint &d) {
            return rotate(a, b, c) * rotate(a, b, d) <= 0 && rotate(c, d, a) * rotate(c, d, b) < 0;
        }


        double m_beginT; //Time start Up
        std::vector<TMBrickPoint> m_points;
        std::vector<TMBrickUp> m_numberUp;
    };
}

#endif //TSUNAMIMANAGER_TMBLOCK_H
