#include "dc_motor.h"
#include "../hexapod/debug.h"

#include "../hexapod/hal/pwm.h"

namespace car { 

auto pwmLeft = hal::PCA9685(0x41);
auto pwmRight = hal::PCA9685(0x40);
bool pwmInited = false;
const static int kFrequency = 120;
const static int kTickUs = 2;


 void initPWM(void) {
            if (pwmInited)
                return;

            pwmLeft.begin();  
            pwmLeft.setPWMFreq(kFrequency);
            pwmRight.begin();  
            pwmRight.setPWMFreq(kFrequency);
            pwmInited = true;
 }


  void DCMotor::init(void) {
        initPWM();
    }

    DCMotor::DCMotor(int wheelIndex) {
        wheelIndex_ = wheelIndex;
    }

    void DCMotor::setSpeed(float angle) {
        initPWM();

        hal::PCA9685* pwm;
        int idx;
        if (pwmIndex_ < 3) {
            pwm = &pwmRight;
            idx = wheel_;
        }
        else {
            pwm = &pwmLeft;
            idx = wheel_ - 2;
        }

        int us = 4095;
        pwm->setPWM(idx, 0, us/kTickUs);
        LOG_DEBUG("setSpeed%.2f, %d)", angle, us);
    }

    float DCMotor::getSpeed(void) {
        return speed_;
    }
}