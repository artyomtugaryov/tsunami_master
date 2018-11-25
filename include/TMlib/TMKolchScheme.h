#ifndef TSUNAMIMANAGER_TMKOLCHSCHEMA_H
#define TSUNAMIMANAGER_TMKOLCHSCHEMA_H

#include "TMlib/TMScheme.h"
#include "TMlib/TMMapAreaWorker.h"

#include <vector>

namespace TM {
    namespace Scheme {
        class KolchSchema : public Scheme {
        public:
            KolchSchema() = default;

            virtual ~KolchSchema() = default;

            void calculation(MapAreaWorker &,
                             const double &);

            void configure(const MapAreaWorker &,
                           const Focus::Focus &,
                           const double &);

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


#endif //TSUNAMIMANAGER_TMKOLCHSCHEMA_H
