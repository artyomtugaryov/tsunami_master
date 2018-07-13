#ifndef TMCOMMON_H
#define TMCOMMON_H

#include "TMLib/TMConstants.h"

namespace TM {
    namespace Common {
        double coefKoriolis(const double &lat);

        double coefKoriolis_kolch(const double &lat);
    }
}

#endif // TMCOMMON_H
