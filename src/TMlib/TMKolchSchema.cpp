#include <TMlib/TMKolchSchema.h>
#include <TMlib/TMCommon.h>

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

}

void TM::Scheme::TMKolchSchema::set_delta(const std::shared_ptr<const TM::Map::MapArea<double>> &area) {
    delta_x_m = area->stepX() * M_PI * R_EACH / 180;
    for (int j = 0; j < area->sizeY(); ++j) {
        delta_y_m[j] = delta_x_m * cos((area->startY() + j * area->startY()) / 180.0 * M_PI);
        delta_t[j] = 1;
        auto v = sqrt(delta_y_m[j] * delta_y_m[j] + delta_x_m * delta_x_m) / sqrt(2 * G * 3000);
        if (delta_t[j] > v)
            delta_t[j] = v;
    }
}

double
TM::Scheme::TMKolchSchema::converting_motion_blocks(const std::size_t &j, const std::size_t &i, const double &t) {
    double temp_speed; // speed of terr on every interval of time
    for (std::size_t b = 0; b < m_focus->getBlockCount(); b++) {
        if (terr_up[j][i] == b + 1) {
            if (m_focus->getBlock(b).number_up() == 1) {
                if (t * delta_t[j] <= m_focus->getBlock(b).m_numberUp[0].m_brickUpT &&
                    //if (t*delta_t[j] <= t_h_v_up[10][b] &&
                    t * delta_t[j] >= m_focus->getBlock(b).m_beginT) {
                    temp_speed = m_focus->getBlock(b).m_numberUp[0].m_heightUp /
                                 (m_focus->getBlock(b).m_numberUp[0].m_brickUpT - m_focus->getBlock(b).m_beginT);
                    return temp_speed * delta_t[j];
                }
            } else { // if there is any interval of time
                if (t * delta_t[j] <= m_focus->getBlock(b).m_numberUp[0].m_brickUpT &&
                    t * delta_t[j] >= m_focus->getBlock(b).m_beginT) {
                    temp_speed = m_focus->getBlock(b).m_numberUp[0].m_heightUp /
                                 (m_focus->getBlock(b).m_numberUp[0].m_brickUpT - m_focus->getBlock(b).m_beginT);
                    return temp_speed * delta_t[j];
                } else {
                    if (t * delta_t[j] >= m_focus->getBlock(b).m_numberUp[0].m_brickUpT) {
                        for (int d = 0; d < m_focus->getBlock(b).number_up(); d++) {
                            if (t * delta_t[j] <=
                                m_focus->getBlock(b).m_numberUp[d + 1].m_brickUpT) { //  t_h_v_up[12 + d * 2][b]) {
                                temp_speed = (m_focus->getBlock(b).m_numberUp[d + 1].m_brickUpT -
                                              m_focus->getBlock(b).m_numberUp[d].m_heightUp) /
                                             (m_focus->getBlock(b).m_numberUp[d + 1].m_brickUpT -
                                              m_focus->getBlock(b).m_numberUp[d].m_brickUpT);
                                return temp_speed * delta_t[j];
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
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
                eta->setDataByIndex(i, j, etaValue + converting_motion_blocks(i, j, t));
            }
        }
        area->setEta(eta);
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
                auto temp = (int) (i * size_y / size_x);
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