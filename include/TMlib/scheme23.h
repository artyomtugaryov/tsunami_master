#ifndef TSUNAMIMANAGER_TMSHEME24_H
#define TSUNAMIMANAGER_TMSHEME24_H

#include "TMlib/map_area_worker.h"
#include "TMlib/map_area.h"
#include "TMlib/scheme.h"

namespace TM {
namespace Scheme {

    class Scheme23 : public Scheme {
    public:
        Scheme23() = default;

        ~Scheme23() override = default;

        void configure(const MapAreaWorker &area,
                       const TM::Focus::Focus &focus,
                       const double &izobata) override;

        void calculation(MapAreaWorker &area,
                         const double &time) override;

        double getTimeStep(const double &phi,
                           const double &dPhi,
                           const double &dTetta,
                           const double &Hm) const;

    private:

        void setUpBArrays(const size_t &x, const size_t &y);


        double calcMainValueEta(MapAreaWorker &area,
                                const std::size_t &j,
                                const std::size_t &k,
                                const double &dt,
                                const double &dPhi,
                                const double &dTetta,
                                const double &tetta,
                                const double &phi,
                                const double &tetta2,
                                const double &tetta_2,
                                const double &M);

        double calcUVelocity(const MapAreaWorker &area,
                             const std::size_t &j,
                             const std::size_t &k,
                             const double &dTetta,
                             const double &M,
                             const double &f,
                             const double &v,
                             const double &u,
                             const double &dt);

        double calcVVelocity(const MapAreaWorker &area,
                             const std::size_t &j,
                             const std::size_t &k,
                             const double &Tetta,
                             const double &dPhi,
                             const double &M,
                             const double &f,
                             const double &v,
                             const double &u,
                             const double &dt);

        double calcBoundaryType1ValueEta(const MapAreaWorker &area,
                                         const std::size_t &j,
                                         const std::size_t &k,
                                         const double &dPhi,
                                         const double &dTetta);

        double calcBoundaryType2ValueEta(const MapAreaWorker &area,
                                         const std::size_t &j,
                                         const std::size_t &k,
                                         const double &dPhi,
                                         const double &dTetta);


        static double gradient(const TM::Map::MapArea<double> &w,
                               const std::size_t &j,
                               const std::size_t &k,
                               const std::array<int, 2> &d,
                               const int &route = 1);

        std::shared_ptr<MapArea<double>> m_B0;
        std::shared_ptr<MapArea<double>> m_B1;
    };
}
}

#endif //TSUNAMIMANAGER_TMSHEME24_H

