#ifndef TM_SCHEME_H
#define TM_SCHEME_H

#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMFocus.h>
#include <TMlib/TMConstants.h>

#include <memory>

namespace TM {
    namespace Scheme {

        class Scheme {
        public:
            Scheme() = default;

            virtual ~Scheme() = default;

            virtual void calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &,
                                     const double &) = 0;

            virtual void configure(const std::shared_ptr<const TM::Map::MapAreaWorker> &,
                                   const std::shared_ptr<const TM::Focus::Focus> &,
                                   const double &) = 0;

        protected:
            void setTypesOfCells(const std::shared_ptr<const TM::Map::MapAreaWorker> &area,
                                 const double &izobata);
            virtual void setBoundary1Coef(const std::shared_ptr<const TM::Map::MapAreaWorker> &area,
                                          const std::size_t &i, const std::size_t &j,
                                          const double &izobata) = 0;
            virtual void setBoundary2Coef(const std::shared_ptr<const TM::Map::MapAreaWorker> &area,
                                          const std::size_t &i, const std::size_t &j,
                                          const double &izobata) = 0;

            std::shared_ptr<TM::Focus::Focus> m_focus;
            std::shared_ptr<TM::Map::RectangleMapArea<TM::Map::TypesCells>> m_types_cells;
        };
    }
}

#endif //TM_SCHEME_H
