#ifndef TSUNAMIMANAGER_TMBLOCK_H
#define TSUNAMIMANAGER_TMBLOCK_H

#include "TMBrickUp.h"
#include "TMBrickPoint.h"
#include <vector>

namespace TM {
    namespace Focus {
        class Block {
        public:
            Block() : m_beginT(0.0) {}

            bool has(const double &lat, const double &lon);

            double getUpHeight(const double &t);

            void buildBlock(std::vector<TM::Focus::BrickPoint> &points);

            bool pointLocation(const TM::Focus::BrickPoint &a);

            double& get_beginT();

            std::vector<BrickPoint> &get_points();

            std::vector<BrickUp> &get_numberUp();

        private:
            /**
             * Time start Up
             * */
            double m_beginT;
            std::vector<TM::Focus::BrickPoint> m_points;
            std::vector<BrickUp> m_numberUp;
        };
    }
}

#endif //TSUNAMIMANAGER_TMBLOCK_H
