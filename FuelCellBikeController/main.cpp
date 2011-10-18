// Arduino stuff
#include <math.h>
#include <WProgram.h>
#include "arduino_error_handling.h"

// External libraries
#include "libraries/LiquidCrystal/LiquidCrystal.h"
#include "libraries/OneWire/OneWire.h"
#include "libraries/DallasTemperature/DallasTemperature.h"

// Custom stuff
#include "constants.h"
#include "functions.h"
#include "hardware/voltage_sensing.h"
#include "hardware/current_sensing.h"
#include "hardware/pressure_sensing.h"
#include "hardware/temperature_sensing.h"
#include "hardware/pot_input.h"
#include "hardware/button_input.h"
#include "hardware/current_control.h"
#include "basic/soc_ocv.h"

// General setup function
#include "setup.h"

// Loop function
#include "tests/current_control.h"

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
