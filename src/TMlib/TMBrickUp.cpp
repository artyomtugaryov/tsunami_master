#include "TMlib/TMBrickUp.h"

TM::Focus::BrickUp::BrickUp(const double &b, const double &h) : m_brickUpT(b), m_heightUp(h) {}

double TM::Focus::BrickUp::get_brickUpT() const {
    return m_brickUpT;
}

double TM::Focus::BrickUp::get_heightUp() const {
    return m_heightUp;
}
