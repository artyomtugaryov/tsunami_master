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
                       const std::size_t &lat_i,
                       const std::size_t &lon_j,
                       const direction &dir) {

                switch (dir) {
                    case direction::X_FORWARD:
                        return w->getDataByIndex(lat_i + 1, lon_j);
                    case direction::X_BACKWARD:
                        return w->getDataByIndex(lat_i - 1, lon_j);
                    case direction::Y_FORWARD:
                        return w->getDataByIndex(lat_i, lon_j + 1);
                    case direction::Y_BACKWARD:
                        return w->getDataByIndex(lat_i, lon_j - 1);
                    default:
                        THROW_TM_EXCEPTION << "Undefined operator T for TM::Scheme::Operators::" << dir;
                }
            }

            template<typename DataType>
            DataType delta(const std::shared_ptr<MapArea<DataType>> &w,
                           const std::size_t &lat_i,
                           const std::size_t &lon_j,
                           const direction &dir) {

                switch (dir) {
                    case direction::X_FORWARD:
                    case direction::Y_FORWARD:
                        return T(w, lat_i, lon_j, dir) - w->getDataByIndex(lat_i, lon_j);
                    case direction::X_BACKWARD:
                    case direction::Y_BACKWARD:
                        return w->getDataByIndex(lat_i, lon_j) - T(w, lat_i, lon_j, dir);
                    default:
                        THROW_TM_EXCEPTION << "Undefined operator delta for TM::Scheme::Operators::" << dir;
                }
            }

            template<typename DataType>
            DataType feature(const std::shared_ptr<MapArea<DataType>> &w,
                             const std::size_t &lat_i,
                             const std::size_t &lon_j,
                             const direction &dir) {

                switch (dir) {
                    case direction::X_FORWARD:
                    case direction::Y_FORWARD:
                        return 1. / 2. * (w->getDataByIndex(lat_i, lon_j) + T(w, lat_i, lon_j, dir));
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
