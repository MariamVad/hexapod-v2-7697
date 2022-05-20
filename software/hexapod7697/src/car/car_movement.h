#pragma once

#include "car_base.h"

namespace car {

    enum CarMovementMode {
        CAR_MOVEMENT_STANDSTILL = 0,
        CAR_MOVEMENT_FORWARD,
        CAR_MOVEMENT_TURNLEFT,
        CAR_MOVEMENT_TURNRIGHT,

        CAR_MOVEMENT_TOTAL,
    };

    inline CarMovementMode operator++ (CarMovementMode& m, int) {
        if (m < CAR_MOVEMENT_TOTAL)
            m = static_cast<CarMovementMode>(static_cast<int>(m) + 1);
        return m;
    }

    struct CarMovementTable {
        const CarLocations* table;
    };

    class CarMovement {
    public:
        CarMovement(CarMovementMode mode);

        const CarMovementTable& setMode(CarMovementMode newMode);

        const CarWheelPoints& next(int elapsed);

    private:
        CarMovementMode mode_;
        CarLocations position_;
        int index_;             // index in mode position table
        bool transiting_;       // if still in transiting to new mode
        int remainTime_;
    };

}