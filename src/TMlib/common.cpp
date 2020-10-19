#include <math.h>
#include "TMlib/common.h"
#include "TMlib/constants.h"

double TM::Common::coefKoriolis(const double &lat) {
    return 2. * (2. * M_PI / TM::Constants::T_EACH) * cos(lat);
}

double TM::Common::coefKoriolis_kolch(const double &lat) {
    return 2 * TM::Constants::speed_of_earth * cos(lat / 180.0 * M_PI);
}