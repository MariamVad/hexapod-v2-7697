#include "car_movement.h"
#include "../hexapod/debug.h"
#include "config.h"
#include "car_movement_table.h"

#include <cstdlib>

namespace car {

    // extern const CarMovementTable& carStandStillTable();
    // extern const CarMovementTable& carMoveForwardTable();
    // extern const CarMovementTable& carTurnLeftTable();
    // extern const CarMovementTable& carTurnRightTable();

    const CarLocations car_stand_still_paths[] {{{0, 0, 0, 0}}};
    const CarLocations car_move_forward_paths[] {{{4095, 4095, 4095, 4095}}};
    const CarLocations car_turn_left_paths[] {{{4095, 4095, 0, 0}}};
    const CarLocations car_turn_right_paths[] {{{0, 0, 4095, 4095}}};

    const CarMovementTable car_stand_still_table {car_stand_still_paths};
    const CarMovementTable car_move_forward_table {car_move_forward_paths};
    const CarMovementTable car_turn_left_table {car_turn_left_paths };
    const CarMovementTable car_turn_right_table {car_turn_right_paths };



const CarMovementTable& carStandStillTable() {
    return car_stand_still_table;
}

const CarMovementTable& carMoveForwardTable() {
    return car_move_forward_table;
}

const CarMovementTable& carTurnLeftTable() {
    return car_turn_left_table;
}

const CarMovementTable& carTurnRightTable() {
    return car_turn_right_table;
}

    const CarMovementTable kTable[CAR_MOVEMENT_TOTAL] {
        carStandStillTable(),
        carMoveForwardTable(),
        carTurnLeftTable(),
        carTurnRightTable(),
    };

    CarMovement::CarMovement(CarMovementMode mode):
        mode_{mode}, transiting_{false}
    {
    }

    const CarMovementTable& CarMovement::setMode(CarMovementMode newMode) {

        // if (!kTable[newMode].entries) {
        //     LOG_INFO("Error: null movement of mode(%d)!", newMode);
        //     return;
        // }

        mode_ = newMode;

        const CarMovementTable& table = kTable[mode_];
        return table;

     //   index_ = table.entries[std::rand() % table.entriesCount];
      //  remainTime_ = config::movementSwitchDuration > table.stepDuration ? config::movementSwitchDuration : table.stepDuration;
    }

    // const CarWheelPoints& Movement::next(int elapsed) {

    //     const CarMovementTable& table = kTable[mode_];

    //     if (elapsed <= 0)
    //         elapsed = table.stepDuration;

    //     if (remainTime_ <= 0) {
    //         index_ = (index_ + 1)%table.length;
    //         remainTime_ = table.stepDuration;
    //     }
    //     if (elapsed >= remainTime_)
    //         elapsed = remainTime_;

    //     auto ratio = (float)elapsed / remainTime_;
    //     position_ += (table.table[index_] - position_)*ratio;
    //     remainTime_ -= elapsed;

    //     return position_;
    // }
}