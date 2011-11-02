// Arduino stuff
#include <math.h>
#include <WProgram.h>
#include "arduino_error_handling.h"

// External libraries
#include "libraries/LiquidCrystal/LiquidCrystal.h"
#include "libraries/OneWire/OneWire.h"
#include "libraries/DallasTemperature/DallasTemperature.h"
#include "libraries/TimerOne/TimerOne.h"

// Sdfat
#include "libraries/SdFat/SdFat.h"
#include "libraries/SdFat/SdFatUtil.h"
#include "libraries/BufferedWriter/BufferedWriter.h"

// Custom stuff
#include "constants.h"
#include "functions.h"
#include "hardware/lcd_display.h"
#include "hardware/voltage_sensing.h"
#include "hardware/current_sensing.h"
#include "hardware/pressure_sensing.h"
#include "hardware/temperature_sensing.h"
#include "hardware/pot_input.h"
#include "hardware/button_input.h"
#include "hardware/current_control.h"
#include "hardware/sd_storage.h"
#include "basic/soc_ocv.h"
#include "basic/data_acquisition.h"

// General setup function
#include "setup.h"

// Timer interrupt function
#include "timer_interrupt.h"

// Loop function
#include "main_loop.h"

// Let's roll!
int main(void) {

  // arduino init
  init();

  // setup function
  setup();

  // tests can do additional setup
  #ifdef ADDITIONAL_SETUP_PRESENT
    additional_setup();
  #endif
    
  // start timed interval function
  Timer1.initialize(TIMER_INTERVAL);
  Timer1.attachInterrupt(timer_interrupt);

  // loop forever
  for (;;)
    loop();

  return 0;
}
