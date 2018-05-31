#ifndef TSUNAMIMANAGER_TMBRICKPOINT_H
#define TSUNAMIMANAGER_TMBRICKPOINT_H

#include "TMBrickUp.h"
#include <vector>

namespace TM {
    namespace Focus {
        class BrickPoint {
        public:

            BrickPoint() : m_x(0.0), m_y(0.0) {}

            BrickPoint(double x, double y) : m_x(x), m_y(y) {}

            bool operator<(const BrickPoint &other) {
                return (m_x < other.m_x);
            }

            static double rotate(const BrickPoint &a,
                                 const BrickPoint &b,
                                 const BrickPoint &c);

            static bool intersect(const BrickPoint &a,
                                  const BrickPoint &b,
                                  const BrickPoint &c,
                                  const BrickPoint &d);
            double x() const;

            double y() const;

        private:

            double m_x;
            double m_y;
        };
    }
}

#endif //TSUNAMIMANAGER_TMBRICKPOINT_H
