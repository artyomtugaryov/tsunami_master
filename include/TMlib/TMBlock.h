#ifndef TSUNAMIMANAGER_TMBLOCK_H
#define TSUNAMIMANAGER_TMBLOCK_H

#include <vector>
#include <algorithm>

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
            int m_brickUpT; // Time Up the block
            double m_heightUp; // Height Up the  block

            BrickUp(int b, double h) : m_brickUpT(b), m_heightUp(h) {}
        };

        struct Block {
            Block() : m_beginT(0) {

            }

            bool has(double lat, double lon);

            double getUpHeihgt(double t);

            bool pointloc(const BrickPoint &a);

            static double rotate(const BrickPoint &a, const BrickPoint &b, const BrickPoint &c) {
                /*
                 * https://habrahabr.ru/post/144571/
                 */
                return (b.m_x - a.m_x) * (c.m_y - b.m_y) - (b.m_y - a.m_y) * (c.m_x - b.m_x);
            }

            static bool
            intersect(const BrickPoint &a, const BrickPoint &b, const BrickPoint &c, const BrickPoint &d) {
                return ((rotate(a, b, c) * rotate(a, b, d)) <= 0) && ((rotate(c, d, a) * rotate(c, d, b)) < 0);
            }

            void build_block(std::vector<TM::Focus::BrickPoint> points) {
                auto n = points.size();
                std::sort(points.begin(), points.end());
                std::vector<size_t> p(n);
                for (size_t i(0); i < n; i++) {
                    p[i] = i;
                }
                for (size_t i(2); i < n; i++) {
                    size_t j = i;
                    while (j > 1 and rotate(points[p[0]], points[p[j - 1]], points[p[j]]) < 0) {
                        size_t tmp = p[j];
                        p[j] = p[j - 1];
                        p[j - 1] = tmp;
                        j--;
                    }
                }
                m_points.resize(n);
                if (points[*p.begin()].m_y > points[*p.end()].m_y){
                    std::reverse(std::begin(p), std::end(p)-1);
                }
                for (size_t i(0); i < n; i++) {
                    m_points[i] = points[p[i]];
                }
            }


            double m_beginT; //Time start Up
            std::vector<BrickPoint> m_points;
            std::vector<BrickUp> m_numberUp;
        };
    }
}

#endif //TSUNAMIMANAGER_TMBLOCK_H
