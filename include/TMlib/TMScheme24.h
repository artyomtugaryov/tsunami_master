#ifndef TSUNAMIMANAGER_TMSHEME24_H
#define TSUNAMIMANAGER_TMSHEME24_H

#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMMapArea.h>
#include <TMlib/TMScheme.h>

namespace TM {
    namespace Scheme {
        struct BoundaryCoefficients {
            virtual double eta(const std::shared_ptr<TM::Map::MapAreaWorker> &are) = 0;
        };

        struct Boundary1Coefficients {
            Boundary1Coefficients(const std::size_t &x_01, const std::size_t &y_01,
                                  const std::size_t &x_02, const std::size_t &y_02,
                                  const std::size_t &x_10, const std::size_t &y_10,
                                  const std::size_t &x_20, const std::size_t &y_20,
                                  const double &alpha) {
                m_x_01 = x_01;
                m_y_01 = y_01;
                m_x_02 = x_02;
                m_y_02 = y_02;
                m_x_10 = x_10;
                m_y_10 = y_10;
                m_x_20 = x_20;
                m_y_20 = y_20;
                m_alpha = alpha;
            }

            std::size_t m_x_01;
            std::size_t m_y_01;
            std::size_t m_x_02;
            std::size_t m_y_02;
            std::size_t m_x_10;
            std::size_t m_y_10;
            std::size_t m_x_20;
            std::size_t m_y_20;
            double m_alpha;

            double eta(const std::shared_ptr<TM::Map::MapAreaWorker> &area) {
                auto b = area->bathymetry();
                auto eta = area->eta();
                return (b->stepY() *
                        (4 * eta->getDataByIndex(m_x_10, m_y_10) - eta->getDataByIndex(m_x_20, m_y_20) * cos(m_alpha)) +
                        b->stepX() * (4 * eta->getDataByIndex(m_x_01, m_y_01) -
                                      eta->getDataByIndex(m_x_02, m_y_02) * sin(m_alpha))) / 3 *
                       (b->stepY() * cos(m_alpha) + b->stepX() * sin(m_alpha));
            }
        };

        struct Boundary2Coefficients {

        };

        class TMScheme24 : public TMScheme {
        public:
            TMScheme24() = default;

            ~TMScheme24() override = default;

            void calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &area,
                             const double &timeEnd) override;

            void configure(const std::shared_ptr<const Map::MapAreaWorker> &area,
                           const std::shared_ptr<const Focus::Focus> &focus,
                           const double &izobata,
                           const std::shared_ptr<TMTimeManager> &sender,
                           const std::shared_ptr<TMSignal> &signal) override;

            double getTimeStep(const double &dPhi, const double &dTetta, const double &Hm) const;

        private:

            void setUpBArrays(std::size_t &&x, std::size_t &&y);

            void setBoundary1Coef(const std::shared_ptr<const TM::Map::MapAreaWorker> &area, const std::size_t &i,
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

            static double gradient(const std::shared_ptr<const TM::Map::MapArea<double>> &w,
                                   const std::size_t &j,
                                   const std::size_t &k,
                                   const std::array<int, 2> &d,
                                   const int &to = 1);

            std::shared_ptr<TM::Map::MapArea<double>> m_B0;
            std::shared_ptr<TM::Map::MapArea<double>> m_B1;
            std::shared_ptr<TM::Map::MapArea<TM::Scheme::BoundaryCoefficients>> m_Boundaries;

        };
    }
}

#endif //TSUNAMIMANAGER_TMSHEME24_H

