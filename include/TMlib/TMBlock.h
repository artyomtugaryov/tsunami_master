#ifndef TSUNAMIMANAGER_TMBLOCK_H
#define TSUNAMIMANAGER_TMBLOCK_H

#include <vector>
#include <algorithm>

namespace TM {
    struct TMBrickPoint {
    public:
        double m_x;
        double m_y;

        TMBrickPoint() = default;
        TMBrickPoint(double x, double y) : m_x(x), m_y(y) {}

        inline bool operator<(const TMBrickPoint &other) {
            return (m_x < other.m_x);
        }
    };

    struct TMBrickUp {
    public:
        int m_brickUpT; // Time Up the block
        double m_heightUp; // Height Up the  block

        TMBrickUp(int b, double h) : m_brickUpT(b), m_heightUp(h) {}
    };

    struct TMBlock {
        TMBlock() : m_beginT(0) {

        }

        bool has(double lat, double lon);

        double getUpHeihgt(double t);

        bool pointloc(const TMBrickPoint &a);

        static double rotate(const TMBrickPoint &a, const TMBrickPoint &b, const TMBrickPoint &c) {
            /*
             * https://habrahabr.ru/post/144571/
             */
            return (b.m_x - a.m_x) * (c.m_y - b.m_y) - (b.m_y - a.m_y) * (c.m_x - b.m_x);
        }

        static bool
        intersect(const TMBrickPoint &a, const TMBrickPoint &b, const TMBrickPoint &c, const TMBrickPoint &d) {
            return ((rotate(a, b, c) * rotate(a, b, d)) <= 0) && ((rotate(c, d, a) * rotate(c, d, b)) < 0);
        }


        void build_block(std::vector<TM::TMBrickPoint> points) {
            auto n = points.size();
            std::sort(points.begin(), points.end());
            std::vector<size_t> p(n);
            for(size_t i(0); i< n; i++){
                p[i] = i;
            }
            for (size_t i(2); i < n; i++) {
                size_t j = i;
                while (j > 1 and rotate(points[p[0]], points[p[j - 1]], points[p[j]])) {
                    size_t tmp = p[j];
                    p[j] = p[j - 1];
                    p[j - 1] = tmp;
                    j--;
                }
            }
            m_points.resize(n);
            for (size_t i(0); i < n; i++) {
                m_points[i] = points[p[i]];
            }
        }


        double m_beginT; //Time start Up
        std::vector<TMBrickPoint> m_points;
        std::vector<TMBrickUp> m_numberUp;
    };
}

#endif //TSUNAMIMANAGER_TMBLOCK_H
