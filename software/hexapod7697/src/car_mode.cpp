#include <Arduino.h>

#ifndef __LREMOTE_H__
#include "LRemote.h"
#define __LREMOTE_H__
#endif

#include "linkit_control/ui_controls.h"
#include "hexapod/debug.h"
#include "hexapod/hexapod.h"
#include "car_mode.h"
#include "car/config.h"
#include "car/car.h"

//#define REACT_DELAY hexapod::config::movementInterval
#define REACT_DELAY car::config::movementInterval

static Button buttonCarForward(car::CAR_MOVEMENT_FORWARD, "Move Forward", 1, 0, 1, 1, RC_BLUE);
static Button buttonCarLeft(car::CAR_MOVEMENT_TURNLEFT, "Turn Left", 0, 2, 1, 1, RC_GREEN);
static Button buttonCarRight(car::CAR_MOVEMENT_TURNRIGHT, "Turn Right", 2, 2, 1, 1, RC_ORANGE);

static ButtonGroup btnGroup;


void car_setup(void) {
  LRemote.setName("PARASITE");
  LRemote.setOrientation(RC_PORTRAIT);
  LRemote.setGrid(3, 5);

  LRemote_addControls({
    &buttonCarForward, 
	&buttonCarLeft,
	&buttonCarRight,
  });
  btnGroup.addControls({
    &buttonCarForward, 
	&buttonCarLeft,
	&buttonCarRight,
  });

  LRemote.begin();
}

void car_loop(void) {

  // check if we are connect by some 
  // BLE central device, e.g. an mobile app
  if(!LRemote.connected()) {
    delay(1000-REACT_DELAY);
  }

  auto t0 = millis();

  // Process the incoming BLE write request
  // and translate them to control events
  LRemote.process();  

  auto flag = btnGroup.getPressFlag();
  auto mode = car::CAR_MOVEMENT_STANDSTILL;
  for (auto m = car::CAR_MOVEMENT_STANDSTILL; m < car::CAR_MOVEMENT_TOTAL; m++) {
    if (flag & (1<<m)) {
      mode = m;
      break;
    }
  }
  Serial.print("mode   ");
    Serial.print(mode);

  car::Car.processMovement(mode, REACT_DELAY);

  auto spent = millis() - t0;

  if(spent < REACT_DELAY) {
     Serial.println(spent);
    delay(REACT_DELAY-spent);
  }
  else {
    Serial.println(spent);
  }
}
