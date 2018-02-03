#ifndef TMCOMMON_H
#define TMCOMMON_H

#include <cmath>
#include "TMConstants.h"

namespace TM{
    namespace Common{
        double coefCoriolis(double lat);
        double sinx(double x);
    }
}


#endif // TMCOMMON_H
