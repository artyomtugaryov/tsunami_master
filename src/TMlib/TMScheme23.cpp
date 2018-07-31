#include <TMlib/TMScheme23.h>
#include <TMlib/TMCommon.h>
#include <TMlib/TMOperators.hpp>
#include <TMlib/TMException.h>
#include <TMlib/TMHelpers.h>
#include <cmath>
#include <ctime>
#include <queue>

using namespace TM;
using namespace TM::Scheme;
using namespace TM::Scheme::Operators;
using namespace TM::Common;
using namespace TM::Constants;

void TM::Scheme::TMScheme23::calculation(const std::shared_ptr<MapAreaWorker> &area,
                                         const double &timeEnd) {
    size_t maxX = area->getMaxXIndex();
    size_t maxY = area->getMaxYIndex();
    size_t j(0), k(0);
    auto dPhi = area->getStepPhi();
    auto dTetta = area->getStepTetta();
    clock_t begin = clock();
#pragma omp parallel for private(j)
    for (j = 1; j < maxX; j++) {
        auto tetta = area->getLongitudeByIndex(j);
#pragma omp parallel for private(k)
        for (k = 1; k < maxY; k++) {
            auto phi = area->getLatitudeByIndex(k);
            // TODO: How get t for this?
            auto Up = this->m_focus->getHeightByPoint(tetta, phi, 0);
            auto B = m_B1->getDataByIndex(j, k);
            m_B0->setDataByIndex(j, k, B);
            m_B1->setDataByIndex(j, k, B + Up);
        }
    }
// TODO: DEFINE time step
    auto dt = 1;
    auto newEta = std::make_shared<TM::Map::MapArea<double>>(area->bathymetry());
#pragma omp parallel for shared(dPhi, dTetta, dt) private(j)
    for (j = 1; j < maxX; j++) {
        auto tetta = area->getLongitudeByIndex(j);
        auto tetta2 = area->getLongitudeByIndex(j + 1. / 2.);
        auto tetta_2 = area->getLongitudeByIndex(j - 1. / 2.);
        auto M = dt / (2 * R_EACH * sin(tetta));
#pragma omp parallel for shared(dPhi, dTetta, dt, tetta, tetta2, tetta_2) private(k)
        for (k = 1; k < maxY; k++) {
            auto phi = area->getLatitudeByIndex(k);
            switch (this->m_types_cells->getDataByIndex(j, k)) {
                case WATER: {
                    newEta->setDataByIndex(j, k, this->calcMainValueEta(area,
                                                                        j, k,
                                                                        dt,
                                                                        dPhi, dTetta,
                                                                        tetta, phi,
                                                                        tetta2, tetta_2,
                                                                        M));
                    break;
                }
                case BOUNDARY1: {
                    newEta->setDataByIndex(j, k, this->calcBoundaryType1ValueEta(area,
                                                                                 j, k,
                                                                                 dPhi, dTetta));
                    break;
                }
                case BOUNDARY2: {
                    newEta->setDataByIndex(j, k, this->calcBoundaryType2ValueEta(area,
                                                                                 j, k,
                                                                                 dPhi, dTetta));
                    break;
                }
                case LAND:
                default:
                    break;
            }
        }
    }
    area->setEta(newEta);

    auto newU = std::make_shared<TM::Map::MapArea<double>>(area->bathymetry());
    auto newV = std::make_shared<TM::Map::MapArea<double>>(area->bathymetry());
    auto M = G * dt / R_EACH; //make more common
#pragma omp parallel for shared(M) private(j)
    for (j = 0; j < maxX; j++) {
        auto tetta = area->getLongitudeByIndex(j);
        auto f = coefKoriolis(tetta);
#pragma omp parallel for  shared(f, M) private(k)
        for (k = 0; k < maxY; k++) {
            auto u_new = 0.;
            auto v_new = 0.;
            if (this->m_types_cells->getDataByIndex(j, k) == WATER) {
                auto u = area->uVelocity()->getDataByIndex(j, k);
                auto v = area->vVelocity()->getDataByIndex(j, k);
                u_new = calcUVelocity(area, j, k, dTetta, M, f, u, v, dt);
                v_new = calcVVelocity(area, j, k, tetta, dPhi, M, f, u, v, dt);
            }
            newU->setDataByIndex(j, k, u_new);
            newV->setDataByIndex(j, k, v_new);
        }
    }
    area->setU(newU);
    area->setV(newV);
    //TODO: Remove after resolve problem with brick
    saveMapAreaAsImage(newEta, std::string("img/") + std::to_string(0) + std::string(".png"), area->bathymetry());
    area->saveMareographs();
    clock_t end = clock();
    std::cout << "Time of calculation is: " << double(end - begin) * 1000. / CLOCKS_PER_SEC << " ms." << std::endl;
}

double TM::Scheme::TMScheme23::getTimeStep(const double &phi,
                                           const double &dPhi,
                                           const double &dTetta,
                                           const double &Hm) const {

    auto M = sqrt((1.0 + sqrt(pow(coefKoriolis(phi), 2) + 1)) / 2.0);
    auto dt = (M * R_EACH * dPhi * dTetta) / sqrt(G * fabs(Hm) * (dPhi * dPhi + dTetta * dTetta));
    return dt;
}

void TM::Scheme::TMScheme23::configure(const std::shared_ptr<const TM::Map::MapAreaWorker> &area,
                                       const std::shared_ptr<const TM::Focus::Focus> &focus,
                                       const double &izobata) {
    this->setTypesOfCells(area, izobata);
    if (focus) {
        this->m_focus = std::make_shared<TM::Focus::Focus>(*focus);
    } else {
        std::cout << "[ WARNING ] Focus did not set." << std::endl;
        this->m_focus = std::make_shared<TM::Focus::Focus>();
    }
    this->setUpBArrays(area->getMaxXIndex(), area->getMaxXIndex());
    auto dPhi = area->getStepPhi();
    auto dTetta = area->getStepTetta();
    auto Hm = area->getMaxDepth();
}

void TM::Scheme::TMScheme23::setUpBArrays(std::size_t &&x, std::size_t &&y) {
    this->m_B0 = std::make_shared<TM::Map::MapArea<double>>(x, y);
    this->m_B1 = std::make_shared<TM::Map::MapArea<double>>(x, y);
}

double TM::Scheme::TMScheme23::calcMainValueEta(const shared_ptr<MapAreaWorker> &area,
                                                const size_t &j,
                                                const size_t &k,
                                                const double &dt,
                                                const double &dPhi,
                                                const double &dTetta,
                                                const double &tetta,
                                                const double &phi,
                                                const double &tetta2,
                                                const double &tetta_2,
                                                const double &M) {

    auto H_Bj0k0 = feature(area->bathymetry(), j, k, direction::TETTA_FORWARD) - feature(m_B0, j, k, direction::TETTA_FORWARD);
    auto H_Bj_1k0 = feature(area->bathymetry(), j-1, k, direction::TETTA_FORWARD) - feature(m_B0, j-1, k, direction::TETTA_FORWARD);

    auto Hj0k0 = gradient(area->bathymetry(), j, k, std::array<int, 2>({1, 0}));
    auto Hj0k_1 = gradient(area->bathymetry(), j, k - 1, std::array<int, 2>({0, 1}));

    auto Bj0k0 = gradient(m_B0, j, k, std::array<int, 2>({1, 0}));
    auto Bj0k_1 = gradient(m_B0, j, k - 1, std::array<int, 2>({0, 1}));

    auto oldBj0k0 = m_B0->getDataByIndex(j, k);
    auto newBj0k0 = m_B1->getDataByIndex(j, k);

    auto eta0 = area->eta()->getDataByIndex(j, k);

    //Getting velocity
    auto Uj0k0 = area->uVelocity()->getDataByIndex(j, k);
    auto Uj1k0 = area->uVelocity()->getDataByIndex(j + 1, k);
    auto Vj0k0 = area->vVelocity()->getDataByIndex(j, k);
    auto Vj0k1 = area->vVelocity()->getDataByIndex(j, k + 1);

    auto u_multiplier = Uj1k0 * H_Bj0k0 * sin(tetta2) - Uj0k0 * H_Bj_1k0 * sin(tetta_2);
    auto v_multiplier = Vj0k1 * (Hj0k0 - Bj0k0) / 2. - Vj0k0 * (Hj0k_1 - Bj0k_1) / 2.;

    auto eta = eta0 + ((newBj0k0 - oldBj0k0) - M * (u_multiplier / dTetta - v_multiplier / dPhi)) * dt;
    return eta;
}

double TM::Scheme::TMScheme23::calcBoundaryType1ValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                                         const std::size_t &j,
                                                         const std::size_t &k,
                                                         const double &dPhi,
                                                         const double &dTetta) {
    return 0;
}

double TM::Scheme::TMScheme23::calcBoundaryType2ValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                                         const std::size_t &j,
                                                         const std::size_t &k,
                                                         const double &dPhi,
                                                         const double &dTetta) {
    return 0;
}

double TM::Scheme::TMScheme23::calcUVelocity(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                             const std::size_t &j,
                                             const std::size_t &k,
                                             const double &dTetta,
                                             const double &M,
                                             const double &f,
                                             const double &u,
                                             const double &v,
                                             const double &dt) {
    auto dEtaByTetta = gradient(area->eta(), j + 1, k, std::array<int, 2>({-1, 0}), -1);
    return u - M * dEtaByTetta / dTetta + f * v * dt;
}

double TM::Scheme::TMScheme23::calcVVelocity(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                             const std::size_t &j,
                                             const std::size_t &k,
                                             const double &Tetta,
                                             const double &dPhi,
                                             const double &M,
                                             const double &f,
                                             const double &u,
                                             const double &v,
                                             const double &dt) {
    auto dEtaByPhi = gradient(area->eta(), j, k, std::array<int, 2>({0, -1}), -1);
    return v - M * dEtaByPhi / (sin(Tetta) * dPhi) - f * u * dt;
}


double TM::Scheme::TMScheme23::gradient(const std::shared_ptr<const TM::Map::MapArea<double>> &w,
                                        const std::size_t &j,
                                        const std::size_t &k,
                                        const std::array<int, 2> &d,
                                        const int &to) {
    return w->getDataByIndex(j, k) + to * w->getDataByIndex(j + d[0], k + d[0]);
}