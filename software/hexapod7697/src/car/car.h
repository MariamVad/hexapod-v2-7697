#pragma once

#include "car_movement.h"
#include "wheel.h"

namespace car {

    class CarClass {
    public:
        CarClass();

        // init

        void init(bool setting = false);

        // Movement API

        void processMovement(CarMovementMode mode, int elapsed = 0);

        // Calibration API

        void calibrationSave(); // write to flash
        void calibrationGet(int wheelIndex);  // read servo setting
        void calibrationSet(int wheelIndex);    // update servo setting
        void calibrationTest(int wheelIndex);             // test servo setting

    private:
        void calibrationLoad(); // read from flash

    private:
        CarMovementMode mode_;
        CarMovement movement_;
        Wheel wheels_[4];
    };

    extern CarClass Car;
}