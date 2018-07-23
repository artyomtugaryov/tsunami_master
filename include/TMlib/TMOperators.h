#ifndef TSUNAMIMANAGER_OPERATORS_H
#define TSUNAMIMANAGER_OPERATORS_H

#include <iostream>

#include "TMlib/TMMapArea.h"
#include "TMException.h"

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
            DataType T(const std::shared_ptr<MapArea<DataType>> &w,
                                              const double &latitude,
                                              const double &longitude,
                                              const direction &dir) {

                switch (dir) {
                    case direction::X_FORWARD:
                        return w->getDataByPoint(latitude + w->stepX(), longitude);
                    case direction::X_BACKWARD:
                        return w->getDataByPoint(latitude - w->stepX(), longitude);
                    case direction::Y_FORWARD:
                        return w->getDataByPoint(latitude, longitude + w->stepY());
                    case direction::Y_BACKWARD:
                        return w->getDataByPoint(latitude, longitude - w->stepY());
                    default:
                        THROW_TM_EXCEPTION << "Undefined operator T for TM::Scheme::Operators::" << dir;
                }
            }

            template<typename DataType>
            DataType delta(const std::shared_ptr<MapArea<DataType>> &w,
                                                  const double &latitude,
                                                  const double &longitude,
                                                  const direction &dir) {

                switch (dir) {
                    case direction::X_FORWARD:
                    case direction::Y_FORWARD:
                        return T(w, latitude, longitude, dir) - w->getDataByPoint(latitude, longitude);
                    case direction::X_BACKWARD:
                    case direction::Y_BACKWARD:
                        return w->getDataByPoint(latitude, longitude) - T(w, latitude, longitude, dir);
                    default:
                        THROW_TM_EXCEPTION << "Undefined operator delta for TM::Scheme::Operators::" << dir;
                }
            }

            template<typename DataType>
            DataType feature(const std::shared_ptr<MapArea<DataType>> &w,
                                                    const double &latitude,
                                                    const double &longitude,
                                                    const direction &dir) {

                switch (dir) {
                    case direction::X_FORWARD:
                    case direction::Y_FORWARD:
                        return 1. / 2. * (w->getDataByPoint(latitude, longitude) + T(w, latitude, longitude, dir));
                    case direction::X_BACKWARD:
                    case direction::Y_BACKWARD:
                    default:
                        THROW_TM_EXCEPTION << "Undefined operator feature for TM::Scheme::Operators::" << dir;
                }
            }
        }
    }
}



#endif //TSUNAMIMANAGER_OPERATORS_H
