#ifndef TSUNAMIMANAGER_TMSHEME24_H
#define TSUNAMIMANAGER_TMSHEME24_H

#include "TMlib/TMMapAreaWorker.h"
#include "TMlib/TMMapArea.h"
#include "TMlib/TMScheme.h"

namespace TM {
    namespace Scheme {

        class TMScheme23 : public TMScheme {
        public:
            TMScheme23() = default;

            ~TMScheme23() override = default;

            void calculation(MapAreaWorker &area,
                             const double &time) override;

            void configure(const MapAreaWorker &area,
                           const Focus::Focus &focus,
                           const double &izobata) override;

            double getTimeStep(const double &phi,
                               const double &dPhi,
                               const double &dTetta,
                               const double &Hm) const;

        private:

            void setUpBArrays(std::size_t &&x, std::size_t &&y);


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

            MapArea<double> m_B0;
            MapArea<double> m_B1;
        };
    }
}

#endif //TSUNAMIMANAGER_TMSHEME24_H

