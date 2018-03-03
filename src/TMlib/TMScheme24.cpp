#include <TMlib/TMScheme24.h>
#include <TMlib/TMCommon.h>
#include <TMlib/TMException.h>
#include <cmath>
#include <ctime>

void TM::Scheme::TMScheme24::calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                         const double &timeEnd) {
    size_t maxX = area->getMaxXIndex();
    size_t maxY = area->getMaxYIndex();
    size_t j(0), k(0);
    auto dPhi = area->getStepPhi();
    auto dTetta = area->getStepTetta();
    clock_t begin = clock();
    for (double t = 0; t <= timeEnd; t += m_time->step()) {
        auto dt = this->m_time->step();
        std::shared_ptr<TM::Map::MapArea<double>> newEta =
                std::make_shared<TM::Map::MapArea<double>>(area->getMaxXIndex(), area->getMaxYIndex(), 0);
#pragma omp parallel for shared(dPhi, dTetta, dt) private(j)
        for (j = 1; j < maxY; j++) {
            auto tetta = area->getLongitudeByIndex(j);
            auto tetta2 = area->getLongitudeByIndex(j + 1. / 2.);
            auto tetta_2 = area->getLongitudeByIndex(j - 1. / 2.);
            auto M = dt / (2 * R_EACH * sin(tetta));
#pragma omp parallel for  shared(dPhi, dTetta, dt, tetta, tetta2, tetta_2) private(k)
            for (k = 1; k < maxX; k++) {
                auto phi = area->getLatitudeByIndex(k);
                switch (this->m_types_cells->getDataByIndex(k, j)) {
                    case WATER: {
                        auto Up = this->m_focus->getHeigthByIndex(phi, tetta, t);
                        m_B0->setDataByIndex(k, j, m_B1->getDataByIndex(k, j));
                        m_B1->setDataByIndex(k, j, m_B1->getDataByIndex(k, j) + Up);
                        newEta->setDataByIndex(k, j, this->calcMainValueEta(area, k, j, dt, dPhi, dTetta, tetta, tetta2,
                                                                            tetta_2, M));
                        break;
                    }
                    case BOUNDARY1: {
                        newEta->setDataByIndex(k, j, this->calcBoundaryType1ValueEta(area, k, j, dPhi, dTetta));
                        break;
                    }
                    case BOUNDARY2: {
                        newEta->setDataByIndex(k, j, this->calcBoundaryType2ValueEta(area, k, j, dPhi, dTetta));
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        auto f = TM::Common::coefCoriolis(j);
        auto M = -(G * dt) / (R_EACH); //make more common
#pragma omp parallel for shared(f, M) private(j)
        for (j = 0; j < maxY; j++) {
            auto tetta = area->getLongitudeByIndex(j);
#pragma omp parallel for  shared(f, M) private(k)
            for (k = 0; k < maxX; k++) {
                auto u_new = 0.;
                auto v_new = 0.;
                switch (this->m_types_cells->getDataByIndex(k, j)) {
                    case WATER: { ;
                        auto v = area->vVelocity()->getDataByIndex(k, j);
                        auto u = area->uVelocity()->getDataByIndex(k, j);
                        u_new = calcUVelocity(area, k, j, tetta, M, f, v, u, dt);
                        v_new = calcVVelocity(area, k, j, dPhi, tetta, M, f, v, u, dt);
                        break;
                    }
                    default:
                        break;
                }
                area->uVelocity()->setDataByIndex(k, j, u_new);
                area->vVelocity()->setDataByIndex(k, j, v_new);
            }
        }

        area->setEta(newEta);
        //TODO: It's no good. How we can do this better?
        if (!fmod(t, m_time->sendingTimeStep())) {
            m_signal->emitSignal(newEta);
        }
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
                                       const std::shared_ptr<const TM::TMFocus> &focus,
                                       const double &izobata,
                                       const std::shared_ptr<TMTimeManager> &sender,
                                       const std::shared_ptr<TMSignal> &signal) {
    this->setTypesOfCells(area, izobata);
    if (focus) {
        this->m_focus = std::make_shared<TM::TMFocus>(*focus);
    } else {
        std::cout << "[ WARNING ] Focus did not set." << std::endl;
        this->m_focus = std::make_shared<TM::TMFocus>();
    }
    this->setUpBArrays(area->getMaxXIndex(), area->getMaxXIndex());
    this->m_time = sender;
    this->m_signal = signal;
    auto dPhi = area->getStepPhi();
    auto dTetta = area->getStepTetta();
    auto Hm = area->bathymetry()->getMinValue();
    this->m_time->setMaxTimeStep(getTimeStep(dPhi, dTetta, Hm));
}

void TM::Scheme::TMScheme24::setTypesOfCells(const std::shared_ptr<const Map::MapAreaWorker> &area,
                                             const double &izobata) {
    this->m_types_cells = std::make_shared<TM::Map::MapArea<TM::Scheme::types_cells>>(area->getMaxXIndex(),
                                                                                      area->getMaxYIndex());
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
            if (v >= izobata)
                types_of_cells->setDataByIndex(i, j, TM::Scheme::types_cells::LAND);
            else
                types_of_cells->setDataByIndex(i, j, TM::Scheme::types_cells::WATER);
            switch (types_of_cells->getDataByIndex(i, j)) {
                case TM::Scheme::types_cells::WATER:
                    try {
                        if (bathymetry->getDataByIndex(i - 1, j - 1) >= izobata ||
                            bathymetry->getDataByIndex(i - 1, j) >= izobata ||
                            bathymetry->getDataByIndex(i - 1, j + 1) >= izobata ||
                            bathymetry->getDataByIndex(i + 1, j - 1) >= izobata ||
                            bathymetry->getDataByIndex(i + 1, j) >= izobata ||
                            bathymetry->getDataByIndex(i + 1, j + 1) >= izobata ||
                            bathymetry->getDataByIndex(i, j - 1) >= izobata ||
                            bathymetry->getDataByIndex(i, j + 1) >= izobata
                                ) {
                            types_of_cells->setDataByIndex(i, j, TM::Scheme::types_cells::BOUNDARY1);
                        }
                    } catch (TM::details::TMException &ex) { //IF index is out of range
                        types_of_cells->setDataByIndex(i, j, TM::Scheme::types_cells::BOUNDARY2);
                    }
                    break;
                case TM::Scheme::types_cells::LAND:
                    break;
                default:
                    THROW_TM_EXCEPTION << "Can not set type of the cell: (" << i << "," << j << ") val is " << v;
            }
        }
    }
    clock_t end = clock();
    std::cout << "Time of setTypesOfCells is: " << static_cast<double>(end - begin) * 1000.0 / double(CLOCKS_PER_SEC)
              << " ms."
              << std::endl;
}

void TM::Scheme::TMScheme24::setUpBArrays(std::size_t &&x, std::size_t &&y) {
    this->m_B0 = std::make_shared<TM::Map::MapArea<double>>(x, y);
    this->m_B1 = std::make_shared<TM::Map::MapArea<double>>(x, y);
}

double TM::Scheme::TMScheme24::calcMainValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                                const std::size_t &k,
                                                const std::size_t &j,
                                                const double &dt,
                                                const double &dPhi,
                                                const double &dTetta,
                                                const double &tetta,
                                                const double &tetta2,
                                                const double &tetta_2,
                                                const double &M) {
    //Getting bathymetry
    auto Hk0j0 = area->bathymetry()->getDataByIndex(k, j);
    auto Hk0j_1 = area->bathymetry()->getDataByIndex(k, j - 1);
    auto Hk_1j0 = area->bathymetry()->getDataByIndex(k - 1, j);

    //Getting height of the upping
    auto oldBk0j0 = m_B1->getDataByIndex(k, j);
    auto oldBk0j_1 = m_B1->getDataByIndex(k, j - 1);
    auto oldBk_1j0 = m_B1->getDataByIndex(k - 1, j);
    auto newBk0j0 = m_B0->getDataByIndex(k, j);

    auto eta0 = area->eta()->getDataByIndex(k, j);

    //Getting velocity
    auto uk0j0 = area->uVelocity()->getDataByIndex(k, j);
    auto uk0j1 = area->uVelocity()->getDataByIndex(k, j + 1);
    auto vk0j0 = area->vVelocity()->getDataByIndex(k, j);
    auto vk1j0 = area->vVelocity()->getDataByIndex(k + 1, j);

    auto u_multiplier = (uk0j1 * (Hk0j0 - oldBk0j0) * sin(tetta2) - uk0j0 * (Hk0j_1 - oldBk0j_1) * sin(tetta_2));
    auto v_multiplier = (vk1j0 * (Hk0j0 - oldBk0j0) - vk0j0 * (Hk_1j0 - oldBk_1j0));

    return eta0 + (oldBk0j0 - newBk0j0) * dt - M * (u_multiplier / dTetta - v_multiplier / dPhi);
}

double TM::Scheme::TMScheme24::calcBoundaryType1ValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                                         const std::size_t &k,
                                                         const std::size_t &j,
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
                                                         const std::size_t &k,
                                                         const std::size_t &j,
                                                         const double &dPhi,
                                                         const double &dTetta) {

}

double TM::Scheme::TMScheme24::calcUVelocity(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                             const std::size_t &k,
                                             const std::size_t &j,
                                             const double &dTetta,
                                             const double &M,
                                             const double &f,
                                             const double &v,
                                             const double &u,
                                             const double &dt) {
    auto etak0j1 = area->eta()->getDataByIndex(k, j + 1);
    return u - M * etak0j1 * dTetta / dTetta + f * v * dt;
}

double TM::Scheme::TMScheme24::calcVVelocity(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                             const std::size_t &k,
                                             const std::size_t &j,
                                             const double &dPhi,
                                             const double &Tetta,
                                             const double &M,
                                             const double &f,
                                             const double &v,
                                             const double &u,
                                             const double &dt) {
    auto etak0j0 = area->eta()->getDataByIndex(k, j);
    return v - M * etak0j0 * dPhi / (sin(Tetta) * dPhi) - f * u * dt;
}
