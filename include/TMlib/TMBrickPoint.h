#ifndef TSUNAMIMANAGER_TMBRICKPOINT_H
#define TSUNAMIMANAGER_TMBRICKPOINT_H

#include <vector>

namespace TM {
    namespace Focus {
        class BrickPoint {
        public:

            BrickPoint(double x=0.0, double y=0.0);

            bool operator<(const BrickPoint &other) const noexcept;

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
