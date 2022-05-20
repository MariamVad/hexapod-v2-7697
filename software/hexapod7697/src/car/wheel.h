#pragma once

#include "car_base.h"
#include "dc_motor.h"

#include <functional>

namespace car{

    class Wheel{
        public:
            Wheel();

        //private:
            DCMotor* dcMotor;
    };

}