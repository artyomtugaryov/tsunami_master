#ifndef TSUNAMIMANAGER_TMKOLCHSCHEMA_H
#define TSUNAMIMANAGER_TMKOLCHSCHEMA_H

#include "TMScheme.h"
#include "TMMapAreaWorker.h"

namespace TM {
    namespace Scheme {
        class TMKolchSchema : public TMScheme {
        public:
            TMKolchSchema() = default;

            virtual ~TMKolchSchema() = default;

            void calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &,
                             const double &) = 0;

            void configure(const std::shared_ptr<const TM::Map::MapAreaWorker> &,
                           const std::shared_ptr<const TM::Focus::Focus> &,
                           const double &,
                           const std::shared_ptr<TMTimeManager> &,
                           const std::shared_ptr<TMSignal> &);

            double getTimeStep(const double &dPhi, const double &dTetta, const double &Hm) const;

        private:
            void set_delta(const std::shared_ptr<const TM::Map::MapArea<double>> &a);
            void converting_motion_blocks(const int j, const int i);
            std::shared_ptr<TM::Map::MapArea<TM::Scheme::types_cells>> m_types_cells;
            std::vector<double> delta_t;
            std::vector<double> delta_y_m;
            double delta_x_m;
        };
    }
}


#endif //TSUNAMIMANAGER_TMKOLCHSCHEMA_H
