#include "TMlib/TMSchemeGroundswell.h"
#include <TMlib/TMException.h>
#include <fstream>

double TM::Scheme::Groundswell::getStepT() {
    return m_stepT;
}

void TM::Scheme::Groundswell::setStepT(double t) {
    m_stepT = t;
}

void TM::Scheme::Groundswell::runSielecki() {

}
