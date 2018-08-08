#ifndef TSUNAMIMANAGER_SHEME_H
#define TSUNAMIMANAGER_SHEME_H

#include "TMlib/TMMapAreaWorker.h"
#include "TMlib/TMFocus.h"
#include "TMlib/TMConstants.h"
#include "TMlib/TMMapAreaWorker.h"

#include <memory>

using namespace TM::Map;
using namespace TM::Focus;

namespace TM {
namespace Scheme {

    class Scheme {
    public:
        Scheme() = default;

        virtual ~Scheme() = default;

        virtual void configure(const MapAreaWorker & area) = 0;

        virtual void calculation(MapAreaWorker & area, const double & time) = 0;
    };
}
}

#endif //TSUNAMIMANAGER_SHEME_H
