#include "TMlib/Operators.h"
#include "TMlib/TMException.h"

template<typename DataType>
DataType TM::Scheme::Operators::T(const std::shared_ptr<const MapArea<DataType>> &w,
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
            THROW_TM_EXCEPTION << "Undefined operator T ";
    }
}

template<typename DataType>
DataType TM::Scheme::Operators::delta(const std::shared_ptr<const MapArea<DataType>> &w,
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
            THROW_TM_EXCEPTION << "Undefined operator T ";
    }
}