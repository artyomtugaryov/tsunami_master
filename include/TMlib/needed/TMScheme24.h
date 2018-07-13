#ifndef TM_TMSHEME24_H
#define TM_TMSHEME24_H

#include "TMlib/TMScheme.h"

namespace TM {
    namespace Scheme {

        //TODO: Documentation
        class TMScheme24 : public Scheme {
        public:
            TMScheme24() = default;

            ~TMScheme24() override = default;

            void calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                             const double &timeEnd) override;

            void configure(const std::shared_ptr<const Map::MapAreaWorker> &area,
                           const std::shared_ptr<const Focus::Focus> &focus,
                           const double &izobata) override;

            double getTimeStep(const double &dPhi, const double &dTetta, const double &Hm) const;

        private:

            void setUpBArrays(std::size_t &&x, std::size_t &&y);

            void setBoundary1Coef(const std::shared_ptr<const TM::Map::MapAreaWorker> &area, const std::size_t &i,
                                  const std::size_t &j,
                                  const double &izobata) override;

            void setBoundary2Coef(const std::shared_ptr<const TM::Map::MapAreaWorker> &area, const std::size_t &i,
                                  const std::size_t &j,
                                  const double &izobata) override;

            double calcMainValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
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

            double calcUVelocity(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                 const std::size_t &j,
                                 const std::size_t &k,
                                 const double &dTetta,
                                 const double &M,
                                 const double &f,
                                 const double &v,
                                 const double &u,
                                 const double &dt);

            double calcVVelocity(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                 const std::size_t &j,
                                 const std::size_t &k,
                                 const double &Tetta,
                                 const double &dPhi,
                                 const double &M,
                                 const double &f,
                                 const double &v,
                                 const double &u,
                                 const double &dt);

            double calcBoundaryType1ValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                             const std::size_t &j,
                                             const std::size_t &k,
                                             const double &dPhi,
                                             const double &dTetta);

            double calcBoundaryType2ValueEta(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                                             const std::size_t &j,
                                             const std::size_t &k,
                                             const double &dPhi,
                                             const double &dTetta);

            static double gradient(const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &w,
                                   const std::size_t &j,
                                   const std::size_t &k,
                                   const std::array<int, 2> &d,
                                   const int &route = 1);

            std::shared_ptr<TM::Map::RectangleMapArea<double>> m_B0;
            std::shared_ptr<TM::Map::RectangleMapArea<double>> m_B1;
        };
    }
}

#endif //TM_TMSHEME24_H
