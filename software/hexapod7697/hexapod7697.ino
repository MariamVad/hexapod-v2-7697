
#include "src/setting_mode.h"
#include "src/normal_mode.h"
#include "src/car_mode.h"

#include "src/hexapod/debug.h"
#include "src/hexapod/hexapod.h"


//
//  mode
//    0:  normal mode
//    1:  setting mode (for servo calibration)
//
static int _mode = 0;
static int body = 0;
float analogValue = 0;



static void log_output(const char* log) {
  Serial.println(log);
}



//
// wait for N secs, enter setting mode if pressed USR button
//
void boot_wait(int wait_for = 2000) {
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(6, INPUT);
  while (wait_for > 0) {
    if (HIGH == digitalRead(6)) {
      _mode = 1;
      break;
    }
    delay(100);
    wait_for -= 100;
  }

  digitalWrite(LED_BUILTIN, LOW);
}

//
//  Do common setup and mode-specific setup
//
void setup() {
  
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  Serial.println("Starting...");

  pinMode(14, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

analogValue = analogRead(14) / 5 * 1023;

if(analogValue > 204 && analogValue < 260)
    body = 1;   //hexapod
else if(analogValue > 102 && analogValue < 143)
    body = 2;    //car



pinMode(12, OUTPUT);
digitalWrite(12, HIGH);
  //
  // Common setup()
  //

  // Initialize GPIO
  pinMode(LED_BUILTIN, OUTPUT);

  // Workaround for beta PCB
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  boot_wait();

  hexapod::initLogOutput(log_output, millis);
  hexapod::Hexapod.init(_mode == 1);

  //
  // Mode-specific setup()
  //

  if (_mode == 0) {
    normal_setup();
    //car_setup();
  }
  else if (_mode == 1) {
    setting_setup();
  }

  Serial.print("Started, mode=");
  Serial.println(_mode);
}

void loop() {
  //car_loop();

  if (_mode == 0) {
    normal_loop();
  }
  else if (_mode == 1) {
    setting_loop();
  }
}

// if(body == 1){
//   if (_mode == 0) {
//       normal_setup();
//       //car_setup();
//     }
//     else if (_mode == 1) {
//       setting_setup();
//     }
// }
// else if(body == 2){
//     car_setup();
// }

//   Serial.print("Started, mode=");
//   Serial.println(_mode);
// }

// void loop() {
//  // car_loop();

// if(body == 1){
//     if (_mode == 0) {
//       normal_loop();
//     }
//     else if (_mode == 1) {
//       setting_loop();
//     }
//  }
//  else if(body == 2)
//     car_loop();

// }
