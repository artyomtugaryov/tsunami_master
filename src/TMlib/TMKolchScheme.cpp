#include <TMlib/TMKolchScheme.h>
#include <TMlib/TMCommon.h>
#include <TMlib/TMHelpers.h>

double TM::Scheme::TMKolchSchema::getTimeStep(const double &dPhi, const double &dTetta, const double &Hm) const {

    auto delta_x_m = dPhi * M_PI * R_EACH / 180;
    auto delta_y_m = delta_x_m * cos((0/*start_y + j * delta_y*/) / 180.0 * M_PI);
    return sqrt(pow(delta_y_m, 2) + pow(delta_x_m, 2)) / sqrt(2 * G * 3000);
}

void TM::Scheme::TMKolchSchema::configure(const std::shared_ptr<const TM::Map::MapAreaWorker> &area,
                                          const std::shared_ptr<const TM::Focus::Focus> &focus,
                                          const double &izobata,
                                          const std::shared_ptr<TMTimeManager> &sender,
                                          const std::shared_ptr<TMSignal> &signal) {
    this->setTypesOfCells(area, izobata);
    this->set_delta(area->bathymetry());
    if (focus) {
        this->m_focus = std::make_shared<TM::Focus::Focus>(*focus);
    } else {
        std::cout << "[ WARNING ] Focus did not set." << std::endl;
        this->m_focus = std::make_shared<TM::Focus::Focus>();
    }
    terr_up.resize(area->bathymetry()->sizeY());
    for (int j = 0; j < area->bathymetry()->endY(); j++) {
        terr_up[j].resize(area->bathymetry()->sizeY());
    }
    this->m_time = sender;
    this->m_signal = signal;
}

void TM::Scheme::TMKolchSchema::set_delta(const std::shared_ptr<const TM::Map::MapArea<double>> &area) {
    delta_x_m = area->stepX() * M_PI * R_EACH / 180;
    delta_y_m.resize(area->sizeY());
    delta_t.resize(area->sizeY());
    for (int j = 0; j < area->sizeY(); ++j) {
        delta_y_m[j] = delta_x_m * cos((area->startY() + j * area->stepY()) / 180.0 * M_PI);
        delta_t[j] = 1;
        auto v = sqrt(delta_y_m[j] * delta_y_m[j] + delta_x_m * delta_x_m) / sqrt(2 * G * 3000);
        if (delta_t[j] > v)
            delta_t[j] = v;
    }
}

void TM::Scheme::TMKolchSchema::calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                            const double &timeEnd) {
    std::size_t size_y = area->bathymetry()->sizeY();
    std::size_t size_x = area->bathymetry()->sizeX();
    auto eta = std::make_shared<TM::Map::MapArea<double>>(area->bathymetry());
    for (size_t t = 0; t < timeEnd; t += 1) {
        auto u_old = area->uVelocity();
        auto v_old = area->vVelocity();
        auto eta_old = area->eta();
        auto h = area->bathymetry();
        for (size_t i = 1; i < size_x - 1; ++i) {
            for (size_t j = 1; j < size_y - 1; ++j) {
                auto etaValue = 0.;
                if (m_types_cells->getDataByIndex(i, j) == TM::Scheme::types_cells::WATER) {
                    if (i < size_x - 2 && j < size_y - 2) {
                        etaValue = eta_old->getDataByIndex(i, j) - delta_t[j] * ((1. / (2. * delta_x_m)) *
                                                                                 (u_old->getDataByIndex(i, j + 1) *
                                                                                  (-h->getDataByIndex(i, j + 1) +
                                                                                   -h->getDataByIndex(i, j)) -
                                                                                  u_old->getDataByIndex(i, j) *
                                                                                  (-h->getDataByIndex(i, j) +
                                                                                   -h->getDataByIndex(i, j - 1))) +
                                                                                 (1 / (2 * delta_y_m[j]) *
                                                                                  (v_old->getDataByIndex(i + 1,
                                                                                                         j) *
                                                                                   (-h->getDataByIndex(i + 1,
                                                                                                       j) +
                                                                                    -h->getDataByIndex(i, j)) -
                                                                                   v_old->getDataByIndex(i,
                                                                                                         j) *
                                                                                   (-h->getDataByIndex(i - 1,
                                                                                                       j) +
                                                                                    -h->getDataByIndex(i,
                                                                                                       j)))));

                    }
                }
                eta->setDataByIndex(i, j, etaValue + m_focus->getHeightByIndex(area->getLongitudeByIndex(i), area->getLatitudeByIndex(j), t));
            }
        }
        area->setEta(eta);
        saveMapAreaAsImage(eta, std::string("img/") + std::to_string(t) + std::string(".png"), area->bathymetry());
        const double Ch = 0.0025;
        auto newU = std::make_shared<TM::Map::MapArea<double>>(area->bathymetry());
        auto newV = std::make_shared<TM::Map::MapArea<double>>(area->bathymetry());
        for (size_t i = 1; i < size_x - 1; ++i) {
            for (size_t j = 1; j < size_y - 1; ++j) {
                auto u = 0.;
                auto v = 0.;
                if (m_types_cells->getDataByIndex(i, j) == TM::Scheme::types_cells::WATER) {
                    u = u_old->getDataByIndex(i, j) -
                        G * delta_t[j] / delta_x_m * (eta->getDataByIndex(i, j) - eta->getDataByIndex(i, j - 1)) -
                        delta_t[j] * Ch / (eta->getDataByIndex(i, j) + -h->getDataByIndex(i, j)) *
                        fabs(u_old->getDataByIndex(i, j)) * u_old->getDataByIndex(i, j);
                    v = v_old->getDataByIndex(i, j) - G * delta_t[j] / delta_y_m[j] *
                                                      (eta->getDataByIndex(i, j) - eta->getDataByIndex(i - 1, j)) -
                        delta_t[j] * Ch / (eta->getDataByIndex(i, j) + -h->getDataByIndex(i, j)) *
                        fabs(v_old->getDataByIndex(i, j)) * v_old->getDataByIndex(i, j);

                }
                newU->setDataByIndex(i, j, u);
                newV->setDataByIndex(i, j, v);
            }
        }
        area->setU(newU);
        area->setV(newV);
        for (std::size_t i = 1; i < size_x; i++) {
            try {
                auto temp = static_cast<int>(i * size_y / size_x);
                newV->setDataByIndex(i, 0, sqrt(fabs(-G * h->getDataByIndex(i, 0))) * eta->getDataByIndex(i, 0) /
                                           (eta->getDataByIndex(i, 1) - h->getDataByIndex(i, 0)));
                newV->setDataByIndex(i, size_y - 2, sqrt(fabs((-G * h->getDataByIndex(i, size_y - 2)))) *
                                                    eta->getDataByIndex(i, size_y - 3) /
                                                    (eta->getDataByIndex(i, size_y - 3) -
                                                     h->getDataByIndex(i, size_y - 2)));
                newV->setDataByIndex(i, size_y - 1, area->vVelocity()->getDataByIndex(i, size_y - 2));
                eta->setDataByIndex(i, 0, eta_old->getDataByIndex(i, 0) -
                                          sqrt(fabs(-h->getDataByIndex(i, 0) * G)) * (delta_t[temp] / delta_y_m[temp]) *
                                          (eta_old->getDataByIndex(i, 0) - eta_old->getDataByIndex(i, 1)));
                eta->setDataByIndex(i, size_y - 2, eta_old->getDataByIndex(i, size_y - 2) -
                                                   sqrt(fabs((-h->getDataByIndex(i, size_y - 2) * G))) *
                                                   (delta_t[temp] / delta_y_m[temp]) *
                                                   (eta_old->getDataByIndex(i, size_y - 2) -
                                                    eta_old->getDataByIndex(i, size_y - 3)));
                eta->setDataByIndex(i, size_y - 1, eta->getDataByIndex(i, size_y - 2));
            }
            catch (...) {
            }
        }
        for (std::size_t j = 1; j < size_y; j++) {
            try {
                newU->setDataByIndex(j, 0, sqrt((-G * h->getDataByIndex(0, j))) * eta->getDataByIndex(1, j) /
                                           (eta->getDataByIndex(1, j) - h->getDataByIndex(0, j)));
                newU->setDataByIndex(j, size_x - 2, newU->getDataByIndex(j, size_x - 3));
                newU->setDataByIndex(j, size_x - 1, newU->getDataByIndex(j, size_x - 2));
                eta->setDataByIndex(j, 0, eta_old->getDataByIndex(0, j) -
                                          sqrt(fabs((-h->getDataByIndex(0, j) * G))) * (delta_t[j] / delta_x_m) *
                                          (eta_old->getDataByIndex(0, j) - eta_old->getDataByIndex(1, j)));
                eta->setDataByIndex(j, size_x - 2, eta_old->getDataByIndex(size_x - 2, j) -
                                                   sqrt(fabs((-h->getDataByIndex(size_x - 2, j) * G))) *
                                                   (delta_t[j] / delta_x_m) * (eta_old->getDataByIndex(size_x - 2, j) -
                                                                               eta_old->getDataByIndex(size_x - 3, j)));
                eta->setDataByIndex(j, size_x - 1, newU->getDataByIndex(j, size_x - 2));
            }
            catch (...) {
            }
        }
        if (!fmod(t, m_time->sendingTimeStep())) {
            m_signal->emitSignal(eta);
        }
    }
}
