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
                             const double &);

            void configure(const std::shared_ptr<const TM::Map::MapAreaWorker> &,
                           const std::shared_ptr<const TM::Focus::Focus> &,
                           const double &,
                           const std::shared_ptr<TMTimeManager> &,
                           const std::shared_ptr<TMSignal> &);

        private:
            void set_delta(const std::shared_ptr<const TM::Map::MapArea<double>> &);

            void setBoundary1Coef(const std::shared_ptr<const TM::Map::MapAreaWorker> &,
                                  const size_t &,
                                  const size_t &,
                                  const double &) override {};

            void setBoundary2Coef(const std::shared_ptr<const TM::Map::MapAreaWorker> &,
                                  const size_t &,
                                  const size_t &,
                                  const double &) override {};

            double delta_x_m;
            std::vector<double> delta_t;
            std::vector<double> delta_y_m;
            std::vector<std::vector<int>> terr_up;
        };
    }
}


#endif //TSUNAMIMANAGER_TMKOLCHSCHEMA_H
