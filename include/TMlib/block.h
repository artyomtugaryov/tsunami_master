#ifndef TM_LIB_BLOCK_H
#define TM_LIB_BLOCK_H

#include "TMlib/brick_up.h"
#include "TMlib/brick_point.h"

#include <vector>

namespace TM {
    namespace Focus {
        class Block {
        public:
            Block() : m_beginT(0.0) {}

            bool has(const double &lat, const double &lon);

            double getUpHeight(const double &t);

            void buildBlock(std::vector<BrickPoint> &points);

            bool pointLocation(const BrickPoint &a);

            double &get_beginT();

            std::vector<BrickPoint> &get_points();

            std::vector<BrickUp> &get_numberUp();

        private:
            /**
             * Time start Up
             * */
            double m_beginT;
            std::vector<BrickPoint> m_points;
            std::vector<BrickUp> m_numberUp;
        };
    }
}

#endif //TM_LIB_BLOCK_H
