// Arduino stuff
#include <WProgram.h>
#include "arduino_error_handling.h"

// External libraries
#include "libraries/LiquidCrystal/LiquidCrystal.h"
#include "libraries/OneWire/OneWire.h"
#include "libraries/DallasTemperature/DallasTemperature.h"

// Custom stuff
#include "constants.h"
#include "functions.h"
#include "sensors/voltage.h"
#include "sensors/pressure.h"
#include "sensors/temperature.h"

// General setup function
#include "setup.h"

// Loop function
#include "hardware_tests/current_fc_mot.h"

// Let's roll!
int main(void) {

  init();

  setup();

  #ifdef ADDITIONAL_SETUP_PRESENT
    additional_setup();
  #endif
    
  for (;;)
    loop();

  return 0;
}
