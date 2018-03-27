#include <TMlib/TMKolchSchema.h>
#include <TMlib/TMCommon.h>

double TM::Scheme::TMKolchSchema::getTimeStep(const double &dPhi, const double &dTetta, const double &Hm) const {

    auto delta_x_m = dPhi * M_PI * R_EACH / 180;
    auto delta_y_m = delta_x_m * cos((start_y + j * delta_y) / 180.0 * M_PI);
    return sqrt(pow(delta_y_m, 2) + pow(delta_x_m, 2)) / sqrt(2 * G * 3000);
}

void TM::Scheme::TMKolchSchema::configure(const std::shared_ptr<const TM::Map::MapAreaWorker> &area,
                                          const std::shared_ptr<const TM::Focus::Focus> &focus,
                                          const double &izobata,
                                          const std::shared_ptr<TMTimeManager> &sender,
                                          const std::shared_ptr<TMSignal> &signal) {
    this->setTypesOfCells(area, izobata);
}

void TM::Scheme::TMKolchSchema::calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                            const double &timeEnd) {
    std::size_t size_y = area->bathymetry()->sizeY();
    std::size_t size_x = area->bathymetry()->sizeX();
    auto eta = std::make_shared<TM::Map::MapArea<double>>(area->eta());
    for (size_t t = 0; t < timeEnd; t += 1) {
        for (size_t j = 1; j < size_y - 1; ++j) {
            auto coefKoriolis = TM::Common::coefKoriolis_kolch(area->getLongitudeByIndex(j));
            auto delta_x_m = area->getStepPhi() * M_PI * R_EACH / 180;
            for (size_t i = 1; i < size_x - 1; ++i) {
                switch (m_types_cells->getDataByIndex(i, j)) {
                    auto dt = getTimeStep(0, 0, 0);
                    case TM::Scheme::types_cells::WATER:
                        if (i < size_x - 2 && j < size_y - 2) {
                            eta->setDataByIndex(i, j, area->eta()->getDataByIndex(j, i) - dt * ((1 / (2 * delta_x_m)) *
                                                                                                (u_old[j + 1][i] *
                                                                                                 (-h[j + 1][i] +
                                                                                                  -h[j][i]) -
                                                                                                 u_old[j][i] *
                                                                                                 (-h[j][i] +
                                                                                                  -h[j -
                                                                                                     1][i])) +
                                                                                                (1 /
                                                                                                 (2 * delta_y_m[j]) *
                                                                                                 (v_old[j][i + 1] *
                                                                                                  (-h[j][i + 1] +
                                                                                                   -h[j][i]) -
                                                                                                  v_old[j][i] *
                                                                                                  (-h[j][i - 1] +
                                                                                                   -h[j][i]))));
                        }

                }
            }
        }
    }

}