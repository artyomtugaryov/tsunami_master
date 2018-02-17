#include <math.h>
#include "TMlib/TMCommon.h"

double TM::Common::coefCoriolis(double lat) {
    return 2.0 * (2.0 * M_PI / T_EACH) * sin(lat);
}