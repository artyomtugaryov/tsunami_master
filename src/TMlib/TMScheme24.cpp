#include <TMlib/TMScheme24.h>
#include <TMlib/TMCommon.h>
#include <TMlib/TMException.h>
#include <TMlib/TMHelpers.h>
#include <cmath>
#include <ctime>
#include <queue>

void TM::Scheme::TMScheme24::calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                         const double &timeEnd) {
    size_t maxX = area->getMaxXIndex();
    size_t maxY = area->getMaxYIndex();
    size_t j(0), k(0);
    auto dPhi = area->getStepPhi();
    auto dTetta = area->getStepTetta();
    clock_t begin = clock();
    for (double t = 0; t <= timeEnd; t += m_time->step()) {
#pragma omp parallel for private(j)
        for (j = 1; j < maxX; j++) {
            auto tetta = area->getLongitudeByIndex(j);
#pragma omp parallel for private(k)
            for (k = 1; k < maxY; k++) {
                if (this->m_types_cells->getDataByIndex(j, k) == WATER) {
                    auto phi = area->getLatitudeByIndex(k);
                    auto Up = this->m_focus->getHeightByIndex(tetta, phi, t);
                    auto B = m_B1->getDataByIndex(j, k);
                    m_B0->setDataByIndex(j, k, B);
                    m_B1->setDataByIndex(j, k, B + Up);
                }
            }
        }
        auto dt = this->m_time->step();
        std::shared_ptr<TM::Map::MapArea<double>> newEta =
                std::make_shared<TM::Map::MapArea<double>>(area->bathymetry());
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
        auto M = G * dt / R_EACH; //make more common
#pragma omp parallel for shared(M) private(j)
        for (j = 0; j < maxX; j++) {
            auto tetta = area->getLongitudeByIndex(j);
            auto f = TM::Common::coefCoriolis(tetta);
#pragma omp parallel for  shared(f, M) private(k)
            for (k = 0; k < maxY; k++) {
                auto u_new = 0.;
                auto v_new = 0.;
                switch (this->m_types_cells->getDataByIndex(j, k)) {
                    case WATER: { ;
                        auto u = area->uVelocity()->getDataByIndex(j, k);
                        auto v = area->vVelocity()->getDataByIndex(j, k);
                        u_new = calcUVelocity(area, j, k, dTetta, M, f, v, u, dt);
                        v_new = calcVVelocity(area, j, k, tetta, dPhi, M, f, v, u, dt);
                        break;
                    }
                    default:
                        break;
                }
                area->uVelocity()->setDataByIndex(j, k, u_new);
                area->vVelocity()->setDataByIndex(j, k, v_new);
            }
        }
        //TODO: It's no good. How we can do this better?
        if (!fmod(t, m_time->sendingTimeStep())) {
            m_signal->emitSignal(newEta);
        }
        //TODO: Remove after resolve problem with brick
//        saveMapAreaAsImage(newEta, std::string("img/") + std::to_string(t) + std::string(".png"), area->bathymetry());
        // END TODO
    }
    clock_t end = clock();
    std::cout << "Time of calculation is: " << double(end - begin) * 1000. / CLOCKS_PER_SEC << " ms." << std::endl;
}

double TM::Scheme::TMScheme24::getTimeStep(const double &dPhi, const double &dTetta, const double Hm) const {

    auto M = sqrt(1.0 + sqrt(TM::Common::coefCoriolis(0) + 1) / 2.0);
    auto dt = (M * R_EACH * dPhi * dTetta) / sqrt(G * fabs(Hm) * (dPhi * dPhi + dTetta * dTetta));
    return dt;
}

void TM::Scheme::TMScheme24::configure(const std::shared_ptr<const TM::Map::MapAreaWorker> &area,
                                       const std::shared_ptr<const TM::Focus::Focus> &focus,
                                       const double &izobata,
                                       const std::shared_ptr<TMTimeManager> &sender,
                                       const std::shared_ptr<TMSignal> &signal) {
    this->setTypesOfCells(area, izobata);
    if (focus) {
        this->m_focus = std::make_shared<TM::Focus::Focus>(*focus);
    } else {
        std::cout << "[ WARNING ] Focus did not set." << std::endl;
        this->m_focus = std::make_shared<TM::Focus::Focus>();
    }
    this->setUpBArrays(area->getMaxXIndex(), area->getMaxXIndex());
    this->m_time = sender;
    this->m_signal = signal;
    auto dPhi = area->getStepPhi();
    auto dTetta = area->getStepTetta();
    auto Hm = area->getMaxDepth();
    this->m_time->setMaxTimeStep(getTimeStep(dPhi, dTetta, Hm));
}

void TM::Scheme::TMScheme24::setTypesOfCells(const std::shared_ptr<const Map::MapAreaWorker> &area,
                                             const double &izobata) {
    this->m_types_cells = std::make_shared<TM::Map::MapArea<TM::Scheme::types_cells>>(area->getMaxXIndex(),
                                                                                      area->getMaxYIndex());
    std::shared_ptr<TM::Map::MapArea<TM::Scheme::types_cells>> boundaries =
            std::make_shared<TM::Map::MapArea<TM::Scheme::types_cells>>(area->getMaxXIndex(), area->getMaxYIndex());
    size_t maxX = this->m_types_cells->sizeX();
    size_t maxY = this->m_types_cells->sizeY();
    auto bathymetry = area->bathymetry();
    auto types_of_cells = this->m_types_cells;
    std::size_t i(0), j(0);
    clock_t begin = clock();
#pragma omp parallel for private(i)
    for (i = 0; i < maxX; i++) {
#pragma omp parallel for shared(bathymetry, types_of_cells) private(j)
        for (j = 0; j < maxY; j++) {
            auto v = bathymetry->getDataByIndex(i, j);
            if (v >= izobata){
                types_of_cells->setDataByIndex(i, j, TM::Scheme::types_cells::LAND);
            }
            else {
                types_of_cells->setDataByIndex(i, j, TM::Scheme::types_cells::WATER);
                for (int k(-1); k < 2; k++) {
                    for (int t(-1); t < 2; t++) {
                        if (k != 0 && t != 0) {
                            try {
                                if (bathymetry->getDataByIndex(i + k, j + t) >= izobata) {
                                    types_of_cells->setDataByIndex(i, j, TM::Scheme::types_cells::BOUNDARY1);
                                }
                            } catch (TM::details::TMException &ex) {
                                types_of_cells->setDataByIndex(i, j, TM::Scheme::types_cells::BOUNDARY2);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    saveMapAreaAsImage(types_of_cells, "boundaries.png", bathymetry);
    clock_t end = clock();
    std::cout << "Time of setTypesOfCells is: "
              << static_cast<double>(end - begin) * 1000.0 / double(CLOCKS_PER_SEC)
              << " ms."
              << std::endl;
}

void TM::Scheme::TMScheme24::setUpBArrays(std::size_t &&x, std::size_t &&y) {
    this->m_B0 = std::make_shared<TM::Map::MapArea<double>>(x, y);
    this->m_B1 = std::make_shared<TM::Map::MapArea<double>>(x, y);
}

double TM::Scheme::TMScheme24::calcMainValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                                const std::size_t &j,
                                                const std::size_t &k,
                                                const double &dt,
                                                const double &dPhi,
                                                const double &dTetta,
                                                const double &tetta,
                                                const double &phi,
                                                const double &tetta2,
                                                const double &tetta_2,
                                                const double &M) {
    auto Hj0k0 = gradient(area->bathymetry(), j, k, std::array<int, 2>({1, 0}));
    auto Hj_1k0 = gradient(area->bathymetry(), j - 1, k, std::array<int, 2>({1, 0}));
    auto Hj0k_1 = gradient(area->bathymetry(), j, k - 1, std::array<int, 2>({0, 1}));

    auto Bj0k0 = gradient(m_B0, j, k, std::array<int, 2>({1, 0}));
    auto Bj_1k0 = gradient(m_B0, j - 1, k, std::array<int, 2>({1, 0}));
    auto Bj0k_1 = gradient(m_B0, j, k - 1, std::array<int, 2>({0, 1}));

    auto oldBj0k0 = m_B0->getDataByIndex(j, k);
    auto newBj0k0 = m_B1->getDataByIndex(j, k);

    auto eta0 = area->eta()->getDataByIndex(j, k);

    //Getting velocity
    auto Uj0k0 = area->uVelocity()->getDataByIndex(j, k);
    auto Uj1k0 = area->uVelocity()->getDataByIndex(j + 1, k);
    auto Vj0k0 = area->vVelocity()->getDataByIndex(j, k);
    auto Vj0k1 = area->vVelocity()->getDataByIndex(j, k + 1);

    auto u_multiplier = Uj1k0 * ((Hj0k0 - Bj0k0) / 2.) * sin(tetta2) - Uj0k0 * (Hj_1k0 - Bj_1k0) / 2. * sin(tetta_2);
    auto v_multiplier = Vj0k1 * (Hj0k0 - Bj0k0) / 2. - Vj0k0 * (Hj0k_1 - Bj0k_1) / 2.;

    auto eta = eta0 + ((newBj0k0 - oldBj0k0) - M * (u_multiplier / dTetta - v_multiplier / dPhi)) * dt;
    return eta;
}

double TM::Scheme::TMScheme24::calcBoundaryType1ValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                                         const std::size_t &j,
                                                         const std::size_t &k,
                                                         const double &dPhi,
                                                         const double &dTetta) {
    auto n01 = 0.;
    auto n02 = 0.;
    auto n10 = 0.;
    auto n20 = 0.;
    auto alpha = 0.;

    return (dPhi * (4 * n10 - n20) * cos(alpha) + dTetta * (4 * n01 - n02) * sin(alpha)) /
           3 * (dPhi * cos(alpha) + dTetta * sin(alpha));
}

double TM::Scheme::TMScheme24::calcBoundaryType2ValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                                         const std::size_t &j,
                                                         const std::size_t &k,
                                                         const double &dPhi,
                                                         const double &dTetta) {
    return 0;
}

double TM::Scheme::TMScheme24::calcUVelocity(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                             const std::size_t &j,
                                             const std::size_t &k,
                                             const double &dTetta,
                                             const double &M,
                                             const double &f,
                                             const double &v,
                                             const double &u,
                                             const double &dt) {
    auto dEtaByTetta = gradient(area->eta(), j + 1, k, std::array<int, 2>({-1, 0}), -1);// Tetta
    return u - M * dEtaByTetta / dTetta + f * v * dt;
}

double TM::Scheme::TMScheme24::calcVVelocity(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                             const std::size_t &j,
                                             const std::size_t &k,
                                             const double &Tetta,
                                             const double &dPhi,
                                             const double &M,
                                             const double &f,
                                             const double &v,
                                             const double &u,
                                             const double &dt) {
    auto dEtaByPhi = gradient(area->eta(), j, k, std::array<int, 2>({0, -1}), -1);
    return v - M * dEtaByPhi / (sin(Tetta) * dPhi) - f * u * dt;
}

double TM::Scheme::TMScheme24::gradient(const std::shared_ptr<const TM::Map::MapArea<double>> &w,
                                        const std::size_t &j,
                                        const std::size_t &k,
                                        const std::array<int, 2> &d,
                                        const int &to) {
    return w->getDataByIndex(j, k) + to * w->getDataByIndex(j + d[0], k + d[0]);
}

std::array<std::size_t, 4> create_n_array(const std::shared_ptr<const TM::Map::MapArea<double>> &bath,
                                          const std::size_t &j,
                                          const std::size_t &k,
                                          const int &izobata) {
    std::queue<std::pair<std::size_t, std::size_t>> points;
    for (int i(-1); i < 2; i++) {
        for (int t(-1); t < 2; t++) {
            try {
                if (bath->getDataByIndex(j + i, k + t) < izobata &&
                    bath->getDataByIndex(j + i - 2, k + t - 2) > izobata) {
                    points.emplace(j + i, k + t);
                }
            } catch (TM::details::TMException &ex) {

            }
        }
    }


};