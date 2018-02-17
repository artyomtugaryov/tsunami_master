#include <math.h>
#include "TMlib/TMCommon.h"

double TM::Common::coefCoriolis(double lat) {
    return 2 * (2 * M_PI / T_EACH)*cos(lat);
}
