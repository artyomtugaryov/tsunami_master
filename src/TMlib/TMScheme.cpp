#include "TMlib/TMScheme.h"
#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMException.h>
#include <TMlib/TMHelpers.h>
#include <ctime>

void TM::Scheme::TMScheme::setTypesOfCells(const std::shared_ptr<const TM::Map::MapAreaWorker> &area,
                                           const double &izobata) {
    this->m_types_cells = std::make_shared<TM::Map::MapArea<TM::Scheme::types_cells>>(area->bathymetry());
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
            if (v >= izobata) {
                types_of_cells->setDataByIndex(i, j, TM::Scheme::types_cells::LAND);
                continue;
            }
            types_of_cells->setDataByIndex(i, j, TM::Scheme::types_cells::WATER);
            for (int k: {-1, 1}) {
                for (int t: {-1, 1}) {
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
            if (types_of_cells->getDataByIndex(i, j) == TM::Scheme::types_cells::BOUNDARY1) {
                setBoundary1Coef(area, i, j, izobata);
            } else {
                if (types_of_cells->getDataByIndex(i, j) == TM::Scheme::types_cells::BOUNDARY2) {
//                    setBoundary2Coef(area, i, j, izobata);
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
