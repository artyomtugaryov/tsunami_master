#ifndef TSUNAMIMANAGER_TMBLOCK_H
#define TSUNAMIMANAGER_TMBLOCK_H

#include <vector>
#include <algorithm>
#include <iostream>

namespace TM {
    namespace Focus {
        struct BrickPoint {
        public:
            double m_x;
            double m_y;

            BrickPoint() = default;

            BrickPoint(double x, double y) : m_x(x), m_y(y) {}

            inline bool operator<(const BrickPoint &other) {
                return (m_x < other.m_x);
            }
        };

        struct BrickUp {
        public:
            double m_brickUpT; // Time Up the block
            double m_heightUp; // Height Up the  block

            BrickUp(int b, double h) : m_brickUpT(b), m_heightUp(h) {}
        };

        struct Block {
            Block() : m_beginT(0) {}

            bool has(double lat, double lon);

            double getUpHeight(double t);

            bool pointLocation(const BrickPoint &a);

            static double rotate(const BrickPoint &a, const BrickPoint &b, const BrickPoint &c);

            static bool intersect(const BrickPoint &a, const BrickPoint &b, const BrickPoint &c, const BrickPoint &d);

            void buildBlock(std::vector<TM::Focus::BrickPoint> points);

            double m_beginT; //Time start Up
            std::vector<BrickPoint> m_points;
            std::vector<BrickUp> m_numberUp;
        };
    }
}

#endif //TSUNAMIMANAGER_TMBLOCK_H
