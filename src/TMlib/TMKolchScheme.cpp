#include <TMlib/TMKolchScheme.h>
#include <TMlib/TMCommon.h>
#include <time.h>
#include <TMlib/TMHelpers.h>

using namespace TM;
using namespace TM::Map;
using namespace TM::Focus;
using namespace TM::Scheme;

void KolchSchema::configure(const MapAreaWorker &area,
                                          const TM::Focus::Focus &focus,
                                          const double &izobata) {
    this->set_delta(area.bathymetry());
    terr_up.resize(area.bathymetry().sizeY());
    for (int j = 0; j < area.bathymetry().endY(); j++) {
        terr_up[j].resize(area.bathymetry().sizeY());
    }
}

void KolchSchema::set_delta(const MapArea<double> &map) {
    delta_x_m = map.stepX() * M_PI * TM::Constants::R_EACH / 180;
    delta_y_m.resize(map.sizeY());
    delta_t.resize(map.sizeY());
    for (int j = 0; j < map.sizeY(); ++j) {
        delta_y_m[j] = delta_x_m * cos((map.startY() + j * map.stepY()) / 180.0 * M_PI);
        delta_t[j] = 1;
        auto v = sqrt(delta_y_m[j] * delta_y_m[j] + delta_x_m * delta_x_m) / sqrt(2 * TM::Constants::G * 3000);
        if (delta_t[j] > v)
            delta_t[j] = v;
    }
}

void KolchSchema::calculation(MapAreaWorker &area,
                                            const double &timeEnd) {
    std::size_t size_y = area.bathymetry().sizeY();
    std::size_t size_x = area.bathymetry().sizeX();
    auto eta = std::make_shared<TM::Map::MapArea<double>>(area.bathymetry());
    for (size_t t = 0; t < timeEnd; t += 1) {
        size_t i = 1, j = 1;
        auto u_old = area.uVelocity();
        auto v_old = area.vVelocity();
        auto eta_old = area.eta();
        auto h = area.bathymetry();
        clock_t begin = clock();
//#pragma omp parallel for shared(u_old, v_old, eta_old, h) private(i)
        for (i = 1; i < size_x - 1; ++i) {
//#pragma omp parallel for shared(u_old, v_old, eta_old, h) private(j)
            for (j = 1; j < size_y - 1; ++j) {
                auto etaValue = 0.;
                if (area.typeOfCell(i, j) == types_cells::WATER) {
                    if (i < size_x - 2 && j < size_y - 2) {
                        etaValue = eta_old.getDataByIndex(i, j) - delta_t[j] * ((1. / (2. * delta_x_m)) *
                                                                                (u_old.getDataByIndex(i, j + 1) *
                                                                                 (-h.getDataByIndex(i, j + 1) +
                                                                                  -h.getDataByIndex(i, j)) -
                                                                                 u_old.getDataByIndex(i, j) *
                                                                                 (-h.getDataByIndex(i, j) +
                                                                                  -h.getDataByIndex(i, j - 1))) +
                                                                                (1 / (2 * delta_y_m[j]) *
                                                                                 (v_old.getDataByIndex(i + 1,
                                                                                                        j) *
                                                                                  (-h.getDataByIndex(i + 1,
                                                                                                     j) +
                                                                                   -h.getDataByIndex(i, j)) -
                                                                                  v_old.getDataByIndex(i,
                                                                                                        j) *
                                                                                  (-h.getDataByIndex(i - 1,
                                                                                                     j) +
                                                                                   -h.getDataByIndex(i,
                                                                                                     j)))));

                    }
                }
                eta->setDataByIndex(i, j, etaValue +
                                          area.focus().getHeightByPoint(area.getLongitudeByIndex(i),
                                                                    area.getLatitudeByIndex(j), t));
            }
        }
        area.setEta(*eta);
//        saveMapAreaAsImage(*eta, std::string("img/") + std::to_string(t) + std::string(".png"), area.bathymetry());
        const double Ch = 0.0025;
        auto newU = std::make_shared<TM::Map::MapArea<double>>(area.bathymetry());
        auto newV = std::make_shared<TM::Map::MapArea<double>>(area.bathymetry());
//#pragma omp parallel for shared(u_old, v_old, h) private(i)
        for (i = 1; i < size_x - 1; ++i) {
//#pragma omp parallel for shared(u_old, v_old, h) private(j)
            for (j = 1; j < size_y - 1; ++j) {
                auto u = 0.;
                auto v = 0.;
                if (area.typeOfCell(i, j) == types_cells::WATER) {
                    u = u_old.getDataByIndex(i, j) -
                        TM::Constants::G * delta_t[j] / delta_x_m *
                        (eta->getDataByIndex(i, j) - eta->getDataByIndex(i, j - 1)) -
                        delta_t[j] * Ch / (eta->getDataByIndex(i, j) + -h.getDataByIndex(i, j)) *
                        fabs(u_old.getDataByIndex(i, j)) * u_old.getDataByIndex(i, j);
                    v = v_old.getDataByIndex(i, j) - TM::Constants::G * delta_t[j] / delta_y_m[j] *
                                                      (eta->getDataByIndex(i, j) - eta->getDataByIndex(i - 1, j)) -
                        delta_t[j] * Ch / (eta->getDataByIndex(i, j) + -h.getDataByIndex(i, j)) *
                        fabs(v_old.getDataByIndex(i, j)) * v_old.getDataByIndex(i, j);

                }
                newU->setDataByIndex(i, j, u);
                newV->setDataByIndex(i, j, v);
            }
        }
        area.setU(*newU);
        area.setV(*newV);
        for (std::size_t i = 1; i < size_x; i++) {
            try {
                auto temp = static_cast<int>(i * size_y / size_x);
                newV->setDataByIndex(i, 0, sqrt(fabs(-TM::Constants::G * h.getDataByIndex(i, 0))) *
                                           eta->getDataByIndex(i, 0) /
                                           (eta->getDataByIndex(i, 1) - h.getDataByIndex(i, 0)));
                newV->setDataByIndex(i, size_y - 2, sqrt(fabs((-TM::Constants::G * h.getDataByIndex(i, size_y - 2)))) *
                                                    eta->getDataByIndex(i, size_y - 3) /
                                                    (eta->getDataByIndex(i, size_y - 3) -
                                                     h.getDataByIndex(i, size_y - 2)));
                newV->setDataByIndex(i, size_y - 1, area.vVelocity().getDataByIndex(i, size_y - 2));
                eta->setDataByIndex(i, 0, eta_old.getDataByIndex(i, 0) -
                                          sqrt(fabs(-h.getDataByIndex(i, 0) * TM::Constants::G)) *
                                          (delta_t[temp] / delta_y_m[temp]) *
                                          (eta_old.getDataByIndex(i, 0) - eta_old.getDataByIndex(i, 1)));
                eta->setDataByIndex(i, size_y - 2, eta_old.getDataByIndex(i, size_y - 2) -
                                                   sqrt(fabs((-h.getDataByIndex(i, size_y - 2) * TM::Constants::G))) *
                                                   (delta_t[temp] / delta_y_m[temp]) *
                                                   (eta_old.getDataByIndex(i, size_y - 2) -
                                                    eta_old.getDataByIndex(i, size_y - 3)));
                eta->setDataByIndex(i, size_y - 1, eta->getDataByIndex(i, size_y - 2));
            }
            catch (...) {
            }
        }
        for (std::size_t j = 1; j < size_y; j++) {
            try {
                newU->setDataByIndex(j, 0,
                                     sqrt((-TM::Constants::G * h.getDataByIndex(0, j))) * eta->getDataByIndex(1, j) /
                                     (eta->getDataByIndex(1, j) - h.getDataByIndex(0, j)));
                newU->setDataByIndex(j, size_x - 2, newU->getDataByIndex(j, size_x - 3));
                newU->setDataByIndex(j, size_x - 1, newU->getDataByIndex(j, size_x - 2));
                eta->setDataByIndex(j, 0, eta_old.getDataByIndex(0, j) -
                                          sqrt(fabs((-h.getDataByIndex(0, j) * TM::Constants::G))) *
                                          (delta_t[j] / delta_x_m) *
                                          (eta_old.getDataByIndex(0, j) - eta_old.getDataByIndex(1, j)));
                eta->setDataByIndex(j, size_x - 2, eta_old.getDataByIndex(size_x - 2, j) -
                                                   sqrt(fabs((-h.getDataByIndex(size_x - 2, j) * TM::Constants::G))) *
                                                   (delta_t[j] / delta_x_m) * (eta_old.getDataByIndex(size_x - 2, j) -
                                                                               eta_old.getDataByIndex(size_x - 3, j)));
                eta->setDataByIndex(j, size_x - 1, newU->getDataByIndex(j, size_x - 2));
            }
            catch (...) {
            }
        }
        clock_t end = clock();
//        std::cout << "Time of one calculation step by time is: "
//                  << static_cast<double>(end - begin) * 1000.0 / double(CLOCKS_PER_SEC)
//                  << " ms."
//                  << std::endl;
    }
}
