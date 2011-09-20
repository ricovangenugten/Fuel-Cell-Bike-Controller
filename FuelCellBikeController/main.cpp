#include <WProgram.h>
#include "arduino.h"

//#include "old_code.h"

#include "constants.h"
#include "setup.h"

#include "hardware_tests/voltage_sensing.h"

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



