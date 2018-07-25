#ifndef TSUNAMIMANAGER_SHEME_H
#define TSUNAMIMANAGER_SHEME_H

#include <memory>
#include <TMlib/TMMapAreaWorker.h>
#include <TMlib/TMFocus.h>
#include <TMlib/TMConstants.h>

using namespace std;

using namespace TM::Map;
using namespace TM::Focus;

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

            virtual void calculation(const shared_ptr<MapAreaWorker> & area,
                                     const double & time) = 0;

            virtual void configure(const shared_ptr<const MapAreaWorker> & area,
                                   const shared_ptr<const Focus::Focus> & focus,
                                   const double & izobata) = 0;

        protected:
            void setTypesOfCells(const shared_ptr<const MapAreaWorker> &area,
                                 const double &izobata);

            shared_ptr<Focus::Focus> m_focus;
            shared_ptr<MapArea<types_cells>> m_types_cells;
        };
    }
}

#endif //TSUNAMIMANAGER_SHEME_H
