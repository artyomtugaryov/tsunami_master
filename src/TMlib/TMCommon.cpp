#include <math.h>
#include "TMlib/TMCommon.h"

double TM::Common::coefCoriolis(double lat) {
    return 2 * (2 * M_PI / T_EACH)*cos(lat);
}

double TM::Common::sinx(double x) {
    /*
     *"Whaaat?" - ask you.
     * It for m = (dt / (2 * R_EACH * sin(tetta))
     * If tetta is 0, m = inf. Need replace sin(x) ~ x
     * */
    double n = x;
    double sum = 0.0;
    int i = 1;

    do {
        sum += n;
        n *= -1.0 * x * x / ((2 * i) * (2 * i + 1));
        i++;
    } while (fabs(n) > 0.000000001);
    return sum;
}