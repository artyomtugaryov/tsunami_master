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

void TM::Scheme::TMKolchSchema::converting_motion_blocks(const int j, const int i) {
    double temp_speed; // speed of terr on every interval of time
    for (int b = 0; b < m_focus->getBlockCount(); b++) {
        /*if (terr_up[j][i] == b + 1) {
            if (terr_number_interval_time[b] == 1) {
                if (t * delta_t[j] <= brick_calc[b].number_up[0].brick_up_t && //if (t*delta_t[j] <= t_h_v_up[10][b] &&
                    t * delta_t[j] >= brick_calc[b].begin_t) {
                    temp_speed = brick_calc[b].number_up[0].height_up /
                                 (brick_calc[b].number_up[0].brick_up_t - brick_calc[b].begin_t);
                    eta[j][i] = eta[j][i] + temp_speed * delta_t[j];
                }
            } else { // if there is any interval of time
                if (t * delta_t[j] <= brick_calc[b].number_up[0].brick_up_t &&
                    t * delta_t[j] >= brick_calc[b].begin_t) {
                    temp_speed = brick_calc[b].number_up[0].height_up /
                                 (brick_calc[b].number_up[0].brick_up_t - brick_calc[b].begin_t);
                    eta[j][i] = eta[j][i] + temp_speed * delta_t[j];
                } else {
                    if (t * delta_t[j] >= brick_calc[b].number_up[0].brick_up_t)
                        for (int d = 0; d < terr_number_interval_time[b]; d++) {
                            if (t * delta_t[j] <=
                                brick_calc[b].number_up[d + 1].brick_up_t) { //  t_h_v_up[12 + d * 2][b]) {
                                temp_speed = (brick_calc[b].number_up[d + 1].height_up -
                                              brick_calc[b].number_up[d].height_up) /
                                             (brick_calc[b].number_up[d + 1].brick_up_t -
                                              brick_calc[b].number_up[d].brick_up_t);
                                eta[j][i] = eta[j][i] + temp_speed * delta_t[j];
                                break;
                            }
                        }
                }
            }
        }
    }*/
    }
    //output_array("c:\\tmp\\eta2.txt", eta);
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
                switch (m_types_cells->getDataByIndex(i, j)) {
                    case TM::Scheme::types_cells::WATER: {
                        if (i < size_x - 2 && j < size_y - 2) {
                            auto etaValue = eta_old->getDataByIndex(i, j) - delta_t[j] * ((1 / (2 * delta_x_m)) *
                                                                                          (u_old->getDataByIndex(i, j +
                                                                                                                    1) *
                                                                                           (-h->getDataByIndex(i,
                                                                                                               j + 1) +
                                                                                            -h->getDataByIndex(i, j)) -
                                                                                           u_old->getDataByIndex(i, j) *
                                                                                           (-h->getDataByIndex(i, j) +
                                                                                            -h->getDataByIndex(i, j -
                                                                                                                  1))) +
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
                            eta->setDataByIndex(i, j, etaValue);
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        const double Ch = 0.0025;

        for (size_t i = 1; i < size_x - 1; ++i) {
            for (size_t j = 1; j < size_y - 1; ++j) {
                auto u = 0.;
                auto v = 0.;
                switch (m_types_cells->getDataByIndex(i, j)) {
                    case TM::Scheme::types_cells::WATER: {
                        u = u_old->getDataByIndex(i, j) - G * delta_t[j] / delta_x_m * (eta->getDataByIndex(i, j) - eta->getDataByIndex(i, j - 1)) - delta_t[j] * Ch / (eta->getDataByIndex(i, j) + -h->getDataByIndex(i, j)) * fabs(u_old->getDataByIndex(i, j)) * u_old->getDataByIndex(i, j);
                        v = v_old->getDataByIndex(i, j) - G * delta_t[j] / delta_y_m[j] * (eta->getDataByIndex(i, j) - eta->getDataByIndex(i - 1, j)) - delta_t[j] * Ch / (eta->getDataByIndex(i, j) + -h->getDataByIndex(i, j)) * fabs(v_old->getDataByIndex(i, j)) * v_old->getDataByIndex(i, j);
                        break;
                    }
                    default: break;
                }
            }
        }
    }
}