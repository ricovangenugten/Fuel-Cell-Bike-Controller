#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd_delay("SD card test");
}

void loop() {

  int loop_start = 0;
  int loop_time = 0;

  // wait for key presses until start of next iteration
  while (millis() % LOOP_INTERVAL) {
    switch (button_down()) {
    case 1:
      // action required
      if (!daq_on()) {
        // start measurement
        if (sd_new_file()) {
          daq_start();
        }
      } else {
        // stop measurement
        daq_stop();
        sd_close_file();
      }
      break;
    }
    delay(1);
  }

  loop_start = millis();

  if (!daq_on()) {
    lcd_message("Daq: Start?");
  }

  loop_time = millis()-loop_start;

  lcd_draw();

}
