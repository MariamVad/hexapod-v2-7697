#pragma once

#include <stdexcept>

namespace car{

    class CarWheelPoints{
        public:
            CarWheelPoints() = default;
            CarWheelPoints(float foreLeft, float hindLeft, float foreRight, float hindRight) 
                : foreLeft_{foreLeft}, hindLeft_{hindLeft}, foreRight_{foreRight}, hindRight_{hindRight} {}

            float foreLeft_;
            float hindLeft_;
            float foreRight_;
            float hindRight_;

    };


    class CarLocations {
    public:
        CarLocations() = default;
        CarLocations(const CarWheelPoints& wheels):
            wheels_{wheels} {
        }
   
        CarWheelPoints wheels_;

    };

}