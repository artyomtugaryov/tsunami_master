#ifndef TSUNAMIMANAGER_SHEME_H
#define TSUNAMIMANAGER_SHEME_H

#include <memory>
#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMFocus.h>
#include <TMlib/TMConstants.h>
#include <TMlib/TMSignal.h>

namespace TM {
    namespace Scheme {
        enum types_cells {
            LAND,
            WATER,
            BOUNDARY1,  //near land
            BOUNDARY2   //end of grid
        };
        class TMScheme {
        public:
            TMScheme() = default;

            virtual ~TMScheme() = default;

            virtual void calculation(const std::shared_ptr<TM::Map::MapAreaWorker>&,
                                     const std::shared_ptr<TMSignal> &,
                                     const double) = 0;

            virtual void configure(const std::shared_ptr<const TM::Map::MapAreaWorker>&,
                                   const std::shared_ptr<const TM::TMFocus>&,
                                   const double &) = 0;
        };
    }
}

#endif //TSUNAMIMANAGER_SHEME_H
