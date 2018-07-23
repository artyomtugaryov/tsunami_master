#ifndef TSUNAMIMANAGER_OPERATORS_H
#define TSUNAMIMANAGER_OPERATORS_H

#include <iostream>

#include "TMlib/TMMapArea.h"

using namespace std;
using namespace TM::Map;

namespace TM {
    namespace Scheme {
        namespace Operators {
            enum direction : unsigned {
                X_FORWARD = 1,
                Y_FORWARD = 2,
                X_BACKWARD = 3,
                Y_BACKWARD = 4
            };

            template<typename DataType>
            DataType T(const std::shared_ptr<const MapArea<DataType>> &w,
                       const double &latitude,
                       const double &longitude,
                       const direction &dir);

            template<typename DataType>
            DataType delta(const std::shared_ptr<const MapArea<DataType>> &w,
                       const double &latitude,
                       const double &longitude,
                       const direction &dir);

            template<typename DataType>
            DataType feature(const std::shared_ptr<const MapArea<DataType>> &w,
                       const double &latitude,
                       const double &longitude,
                       const direction &dir);
        }
    }
}


#endif //TSUNAMIMANAGER_OPERATORS_H
