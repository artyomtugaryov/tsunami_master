#ifndef TMCONSTANTS_H
#define TMCONSTANTS_H

const double R_EACH = 6371000; // meters
const double L_EQUATOR_EACH = 40075696; // meters
const double TIME_TERN_EACH = 24 * 60 * 60; // sec
const double T_EACH = 23 * 60 * 60 + 56 * 60 + 4; //https://en.wikipedia.org/wiki/Coriolis_frequency
const double SPEED_TERN_EACH = L_EQUATOR_EACH / TIME_TERN_EACH; // meters/sec
const double G = 9.8337; // m/sec^2
//KOLCHINA
const double length_of_equator = 40076; //km
const double time_of_turn_earth = 365 * 24 * 60 * 60 + 6 * 60 * 60 + 9 * 60 + 9;
const double speed_of_earth = length_of_equator / time_of_turn_earth;

#endif // TMCONSTANTS_H
