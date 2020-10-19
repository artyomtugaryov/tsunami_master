#ifndef TSUNAMIMANAGER_KolchSchema_H
#define TSUNAMIMANAGER_KolchSchema_H

#include "TMlib/scheme.h"
#include "TMlib/map_area_worker.h"

#include <vector>

namespace TM {
    namespace Scheme {
        class KolchSchema : public Scheme {
        public:
            KolchSchema() = default;

            virtual ~KolchSchema() = default;

            void calculation(MapAreaWorker &,
                             const double &);

            void configure(const MapAreaWorker &area,
                           const TM::Focus::Focus &focus,
                           const double &izobata);

        private:

            void set_delta(const MapArea<double> &map);

        private:

            double delta_x_m;
            std::vector<double> delta_t;
            std::vector<double> delta_y_m;

            std::vector<std::vector<int>> terr_up;
        };
    }
}


#endif //TSUNAMIMANAGER_KolchSchema_H
