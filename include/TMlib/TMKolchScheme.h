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

            void calculation(MapAreaWorker &,
                             const double &);

            void configure(const MapAreaWorker &,
                           const Focus::Focus &,
                           const double &) override ;

        private:
            void set_delta(const MapArea<double> &map);

            double delta_x_m;
            std::vector<double> delta_t;
            std::vector<double> delta_y_m;
            std::vector<vector<int>> terr_up;
        };
    }
}


#endif //TSUNAMIMANAGER_TMKOLCHSCHEMA_H
