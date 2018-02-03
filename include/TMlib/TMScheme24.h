#ifndef TSUNAMIMANAGER_TMSHEME24_H
#define TSUNAMIMANAGER_TMSHEME24_H

#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMMapArea.h>
#include <TMlib/TMFocus.h>
#include <TMlib/TMScheme.h>

namespace TM {
    namespace Scheme {
        class TMScheme24 : public TMScheme {
        public:
            TMScheme24() = default;

            ~TMScheme24() override = default;

            void calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &area) override;

            void configure(const std::shared_ptr<const TM::Map::MapAreaWorker> &area,
                           const std::shared_ptr<const TM::TMFocus> &focus,
                           const double &izobata) override;

            double getTimeStep(const double &dPhi, const double &dTetta) const override;

        private:

            void setTypesOfCells(const std::shared_ptr<const TM::Map::MapAreaWorker> &area,
                                 const double &izobata);

            void setUpBArrays(std::size_t &&x, std::size_t &&y);

            double calcMainValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                    const std::size_t &k, const std::size_t &j,
                                    const double &dt, const double &dPhi,
                                    const double &dTetta, const double &tetta,
                                    const double &tetta2, const double &tetta_2,
                                    const double &M);

            double calcUVelocity(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                 const std::size_t &k,
                                 const std::size_t &j,
                                 const double &dTetta,
                                 const double &M,
                                 const double &f,
                                 const double &v,
                                 const double &u,
                                 const double &dt);

            double calcVVelocity(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                 const std::size_t &k,
                                 const std::size_t &j,
                                 const double &dPhi,
                                 const double &Tetta,
                                 const double &M,
                                 const double &f,
                                 const double &v,
                                 const double &u,
                                 const double &dt);

            double calcBoundaryType1ValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                             const std::size_t &k,
                                             const std::size_t &j,
                                             const double &dPhi,
                                             const double &dTetta);

            double calcBoundaryType2ValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                             const std::size_t &k, const std::size_t &j,
                                             const double &dt, const double &dPhi,
                                             const double &dTetta, const double &tetta,
                                             const double &tetta2, const double &tetta_2,
                                             const double &M);


            std::shared_ptr<TM::Map::MapArea<TM::Scheme::types_cells>> m_types_cells;
            std::shared_ptr<TM::TMFocus> m_focus;
            std::shared_ptr<TM::Map::MapArea<double>> m_B0;
            std::shared_ptr<TM::Map::MapArea<double>> m_B1;

        };
    }
}

#endif //TSUNAMIMANAGER_TMSHEME24_H

