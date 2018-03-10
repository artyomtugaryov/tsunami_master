#ifndef TSUNAMIMANAGER_SHEME_H
#define TSUNAMIMANAGER_SHEME_H

#include <memory>
#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMFocus.h>
#include <TMlib/TMConstants.h>
#include <TMlib/TMTimeManager.h>
#include <TMlib/TMSignal.h>

namespace TM {
    namespace Scheme {
        enum types_cells {
            LAND = 0,
            WATER = 1,
            BOUNDARY1 = 2,  //near land
            BOUNDARY2 = 3   //end of grid
        };

        class TMScheme {
        public:
            TMScheme() = default;

            virtual ~TMScheme() = default;

            virtual void calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &,
                                     const double &) = 0;

            virtual void configure(const std::shared_ptr<const TM::Map::MapAreaWorker> &,
                                   const std::shared_ptr<const TM::Focus::Focus> &,
                                   const double &,
                                   const std::shared_ptr<TMTimeManager> &,
                                   const std::shared_ptr<TMSignal> &) = 0;

        protected:
            std::shared_ptr<TM::Focus::Focus> m_focus;
            std::shared_ptr<TMTimeManager> m_time;
            std::shared_ptr<TMSignal> m_signal;
        };
    }
}

#endif //TSUNAMIMANAGER_SHEME_H
