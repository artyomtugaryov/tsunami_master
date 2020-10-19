#ifndef TM_LIB_SHEME_H
#define TM_LIB_SHEME_H

#include "TMlib/map_area_worker.h"
#include "TMlib/focus.h"

using namespace TM::Map;

namespace TM {
    namespace Scheme {

        class Scheme {
        public:
            Scheme() = default;

            virtual ~Scheme() = default;

            virtual void configure(const MapAreaWorker &area,
                                   const Focus::Focus &focus,
                                   const double &izobata) = 0;

            virtual void calculation(MapAreaWorker &area,
                                     const double &time) = 0;
        };
    }
}

#endif //TM_LIB_SHEME_H
