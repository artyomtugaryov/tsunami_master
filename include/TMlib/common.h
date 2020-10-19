#ifndef TM_LIB_COMMON_H
#define TM_LIB_COMMON_H

#include <cmath>

namespace TM {
    namespace Common {
        double coefKoriolis(const double &lat);

        double coefKoriolis_kolch(const double &lat);
    }
}


#endif // TM_LIB_COMMON_H
