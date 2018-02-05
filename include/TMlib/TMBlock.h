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
            return rotate(a, b, c) * rotate(a, b, d) <= 0 && rotate(c, d, a) * rotate(c, d, b) < 0;
        }


        double m_beginT; //Time start Up
        std::vector<TMBrickPoint> m_points;
        std::vector<TMBrickUp> m_numberUp;
    };
}

#endif //TSUNAMIMANAGER_TMBLOCK_H
