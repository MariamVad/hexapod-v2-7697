#include "car.h"
#include "../hexapod/debug.h"
#include "dc_motor.h"
#include "wheel.h"
#include "car_movement.h"
#include "car_base.h"

// TBD: move to hal
#include <LFlash.h>

namespace car {


    CarClass Car;

    CarClass::CarClass(): 
        wheels_{}, 
        movement_{CAR_MOVEMENT_STANDSTILL},
        mode_{CAR_MOVEMENT_STANDSTILL}
    {

    }

    void CarClass::init(bool setting) {
        DCMotor::init();

       // LFlash.begin();
        //calibrationLoad();

        // default to standby mode
        if (!setting)
            processMovement(CAR_MOVEMENT_STANDSTILL);

        LOG_INFO("Car init done.");
    }

    void CarClass::processMovement(CarMovementMode mode, int elapsed) {
        if (mode_ != mode) {
            mode_ = mode;
            CarMovementTable table = movement_.setMode(mode_);
            Serial.print("movement table:   ");


            if(mode == 0){
                digitalWrite(10, LOW);
                digitalWrite(11, LOW);
                digitalWrite(2, LOW);
                digitalWrite(3, LOW);
            }
            else if(mode == 1){
                digitalWrite(10, HIGH);
                digitalWrite(11, HIGH);
                digitalWrite(2, HIGH);
                digitalWrite(3, HIGH);
            }
            else if(mode == 3){
                digitalWrite(10, LOW);
                digitalWrite(11, LOW);
                digitalWrite(2, HIGH);
                digitalWrite(3, HIGH);
            }
            else if(mode == 3){
                digitalWrite(10, HIGH);
                digitalWrite(11, HIGH);
                digitalWrite(2, LOW);
                digitalWrite(3, LOW);
            }



          //  Serial.println(table);
          //  Serial.println(table);
          const CarLocations* t = table.table;
          CarWheelPoints w = t->wheels_;
           Serial.print("foreLeft_:   ");
          Serial.println(w.foreLeft_);

        }
     for(int i = 0; i < 4; i++){
         wheels_[i].dcMotor = new car::DCMotor(i);
         wheels_[i].dcMotor->setSpeed(5);
     }


        // auto& location = movement_.next(elapsed);
        // for(int i=0;i<6;i++) {
        //     legs_[i].moveTip(location.get(i));
        // }
    }
}

    // void HexapodClass::calibrationSave() {

    //     short data[6*3*2];

    //     for(int i=0;i<6;i++) {
    //         for(int j=0;j<3;j++) {
    //             int offset, scale;
    //             legs_[i].get(j)->getParameter(offset, scale);
    //             data[2*3*i + 2*j] = (short)offset;
    //             data[2*3*i + 2*j + 1] = (short)scale;
    //         }
    //     }

    //     LFlash.write(
    //         "HEXAPOD",
    //         "CALI",
    //         LFLASH_RAW_DATA,
    //         (const uint8_t *)data,
    //         sizeof(data)
    //     );

    // }

    // void HexapodClass::calibrationGet(int legIndex, int partIndex, int& offset, int& scale) {
    //     legs_[legIndex].get(partIndex)->getParameter(offset, scale);
    // }

    // void HexapodClass::calibrationSet(int legIndex, int partIndex, int offset, int scale) {
    //     legs_[legIndex].get(partIndex)->setParameter(offset, scale);
    // }

    // void HexapodClass::calibrationTest(int legIndex, int partIndex, float angle) {
    //     legs_[legIndex].get(partIndex)->setAngle(angle);
    // }

    // void HexapodClass::calibrationLoad() {
    //     short data[6*3*2] = {0};
    //     uint32_t size = sizeof(data);

    //     LFlash.read(
    //         "HEXAPOD",
    //         "CALI",
    //         (uint8_t *)data,
    //         &size
    //     );

    //     for(int i=0;i<6;i++) {
    //         for(int j=0;j<3;j++) {
    //             legs_[i].get(j)->setParameter(data[2*3*i + 2*j], data[2*3*i + 2*j + 1], false);
    //         }
    //     }
    // }
