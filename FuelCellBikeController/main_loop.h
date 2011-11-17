uint32_t timestamp, id, iter_start = 0;
int32_t bike_velocity, soc_charge, i_fc_setpoint, i_fc, i_bat, i_mot, v_fc, v_bat, pw_fc, pw_bat, pw_mot, p_h2, m_h2 = 0;
int prev_iter_time, iter_usage, iter_counter, i_control_out = 0;
float t_h2, t_mot, t_bat = 0;
bool soc_reset_due, temp_fahrenheit, vel_mph, fc_was_on = false;
bool browsing_menu = true;

void loop() {

  // Wait until iteration start time, meanwhile act on button presses
  while (millis() % ITER_INTERVAL) {

    switch (button_down()) {
    case BUTTON_NEXT:
      if (browsing_menu) {
        menu_next();
      } else {
        switch (menu_page()) {

        case PAGE_CUR_CTRL:
          i_controller_setpoint(i_controller_setpoint()+1e3);
          break;

        }
      }
      break;

    case BUTTON_PREVIOUS:
      if (browsing_menu) {
        menu_prev();
      } else {
        switch (menu_page()) {

        case PAGE_CUR_CTRL:
          i_controller_setpoint(i_controller_setpoint()-1e3);
          break;

        }
      }
      break;

    case BUTTON_ACTION:
      switch(menu_page()) {

      case PAGE_MAIN:
        if (daq_on()) {
          // Daq is on, stop it
          daq_stop();
          sd_close_file();
        } else {
          // Daq is off
          if (!fc_on()) {
            // FC is off, start it
            solenoid_fc_toggle_schedule();
          } else {
            // FC is on, start daq
            if (sd_new_file()) {
              daq_start();
            }
          }
        }
        break;

      case PAGE_SOC:
        // If daq is off schedule soc reset
        if (!daq_on()) {
          soc_reset_due = true;
        }
        break;

      case PAGE_CUR_CTRL:
        // Toggle menu browsing or setpoint choosing
        browsing_menu = !browsing_menu;
        break;

      case PAGE_VELOCITY:
        // Toggle mph or kph
        vel_mph = !vel_mph;
        break;

      case PAGE_TEMP:
        // Toggle Fahrenheit or Celsius
        temp_fahrenheit = !temp_fahrenheit;
        break;

      }
      // When a button is pushed the lcd is updated
      menu_refresh_due_now();
      break;
    }
  }

  // Iteration start, save time
  iter_start = millis();

  // Iteration counter
  if (iter_counter == 10) {
    iter_counter = 1;
  } else {
    iter_counter++;
  }

  // Save current SOC
  soc_charge = soc_current_charge();

  // Velocity measurement, only once every 10 iterations
  if (iter_counter == 1) {
    bike_velocity = vel_bike();
  }

  // Get current control setpoint
  i_fc_setpoint = i_controller_setpoint();

  // Current measurements
  i_fc = i_fuel_cell();
  i_bat = i_battery();
  i_mot = i_motor();

  // Voltage measurements
  v_fc = v_fuel_cell();
  v_bat = v_battery();

  // Power estimation
  pw_fc = int32_t(float(v_fc/1e3)*float(i_fc/1e3));
  pw_bat = int32_t(float(v_bat/1e3)*float(i_bat/1e3));
  pw_mot = int32_t(float(v_bat/1e3)*float(i_mot/1e3));

  // Pressure measurement
  p_h2 = p_tank();

  // Hydrogen mass estimation
  m_h2 = hydrogen_mass(t_h2, p_h2);

  if (daq_on()) {
    // Save data to SD-card
    timestamp = daq_measurement_start();
    id = daq_measurement_id();

    if (id == 0) {
      // Write CSV header line
      // Stats
      sd_bw.putStr("id");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("timestamp (ms)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("prev iter time (ms)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      // Velocity measurement
      sd_bw.putStr("velocity mm/s");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      // SOC estimation
      sd_bw.putStr("Bat SOC (mAh)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("Bat SOC (%)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      // Current control
      sd_bw.putStr("i_fc_setpoint (mA)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("i_fc (mA)");
      // Current measurements
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("i_bat (mA)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("i_mot (mA)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      // Voltage measurements
      sd_bw.putStr("v_fc (mV)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("v_bat (mV)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      // Power estimations
      sd_bw.putStr("pw_fc (W)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("pw_bat (W)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("pw_mot (W)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      // Temperature measurements
      sd_bw.putStr("t_h2 (deg C)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("t_bat (10^-2 deg C)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("t_mot (deg C)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      // Hydrogen supply
      sd_bw.putStr("p_h2 (kPa)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("m_h2_tank (g)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      // Line end
      sd_bw.putStr("\r\n");
      sd_bw.writeBuf();
    }

    // Write CSV line
    // Stats
    sd_bw.putNum(id);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(timestamp);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(prev_iter_time);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    // Velocity measurement
    sd_bw.putNum(bike_velocity);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    // SOC estimation
    sd_bw.putNum(soc_charge);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    // SOC estimation
    sd_bw.putNum(soc_percentage(soc_charge));
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    // Current control
    sd_bw.putNum(i_fc_setpoint);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(i_fc);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    // Current measurements
    sd_bw.putNum(i_bat);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(i_mot);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    // Voltage measurements
    sd_bw.putNum(v_fc);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(v_bat);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    // Power estimations
    sd_bw.putNum(pw_fc);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(pw_bat);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(pw_mot);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    // Temperature measurements
    sd_bw.putNum(roundf(t_h2*100));
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(roundf(t_bat*100));
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(roundf(t_mot*100));
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    // Hydrogen supply
    sd_bw.putNum(p_h2);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(m_h2);
    // Line end
    sd_bw.putStr("\r\n");
    sd_bw.writeBuf();

    daq_measurement_end();
  }

  // Toggle FC solenoid if scheduled
  solenoid_fc_toggle_control();

  // Update current control output
  i_controller_input(i_fc);
  i_control_output(i_controller_output());

  // Alternate temperature measurements, do this last because it can be slow..
  switch(iter_counter) {
    case 1:
      t_tank_request();
      break;
    case 2:
      t_h2 = t_tank();
      break;
    case 3:
      t_motor_request();
      break;
    case 4:
      t_mot = t_motor();
      break;
    case 5:
      t_battery_request();
      break;
    case 6:
      t_bat = t_battery();
      break;
  }

  // Turn battery fan on when temperature is too high or sensor is absent
  if (t_bat > FAN_BAT_T_THRES || t_bat == DEVICE_DISCONNECTED) {
    fan_battery_on();
  } else {
    fan_battery_off();
  }

  // Turn motor fan on when temperature is too high or sensor is absent
  if (t_mot > FAN_MOT_T_THRES || t_mot == DEVICE_DISCONNECTED) {
    fan_motor_on();
  } else {
    fan_motor_off();
  }

  // Turn on motor controller when kick stand is in
  if (kickstand_out()) {
    solenoid_motor_off();
    warning_led_on();
  } else {
    solenoid_motor_on();
    warning_led_off();
  }

  // Refresh lcd if needed
  if (menu_refresh_due()) {

    // Output menu
    lcd.setCursor(0,0);
    switch (menu_page()) {

    // Main page
    case PAGE_MAIN:
      lcd.print("Bike: ");
      if (daq_on()) {
        lcd.print("stop daq? ");
      } else {
        if (!fc_on()) {
          lcd.print("start FC? ");
        } else {
          lcd.print("start daq?");
        }
      }

      lcd.setCursor(0,1);
      if (kickstand_out()) {
        lcd.print("Kickstand is out");
      } else if (daq_on()) {
        lcd.print(sd_file_name);
      } else if (!fc_on()) {
        lcd.print("FC is off.      ");
      } else {
        switch (sd_error()) {
          case 1:
            lcd.print("SD init error   ");
            break;
          case 2:
            lcd.print("SD open error   ");
            break;
          }
      }
      break;

    // Velocity page
    case PAGE_VELOCITY:
      lcd.print("Speed: ");
      if (vel_mph) {
        lcd.print("to km/h? ");
      } else {
        lcd.print("to mph?  ");
      }
      lcd.setCursor(0,1);
      if (vel_mph) {
        lcd.print((vel_bike_odo()*0.6214), 1);
        lcd.print(" mi ");
        lcd.print((bike_velocity*2.23e-3), 1);
        lcd.print(" mph  ");
      } else {
        lcd.print(vel_bike_odo(), 1);
        lcd.print(" km ");
        lcd.print((bike_velocity*3.6e-3), 1);
        lcd.print(" kmh  ");
      }
      break;

    // SOC page
    case PAGE_SOC:
      lcd.print("SOC: ");
      if (soc_reset_due) {
        lcd.print("estimating..");
      } else if (!daq_on()) {
        lcd.print("reset?      ");
      } else {
        lcd.print("            ");
      }
      lcd.setCursor(0,1);
      if (soc_reset_due) {
        lcd.print("                ");
      } else {
        lcd.print(soc_init_val());
        lcd.print(" ");
        lcd.print(soc_percentage(soc_init_val()));
        lcd.print("% ");
        lcd.print(soc_charge);
        lcd.print(" ");
        lcd.print(soc_percentage(soc_charge));
        lcd.print("% ");
      }
      break;

    // Current control page
    case PAGE_CUR_CTRL:
      lcd.print("Cur ctrl: ");
      if (browsing_menu) {
        switch (i_controller_state()) {
        case 0:
          lcd.print("set?  ");
          break;
        case 1:
          lcd.print("no in ");
          break;
        case 2:
          lcd.print("min   ");
          break;
        case 3:
          lcd.print("max   ");
          break;
        }
      } else {
        // choosing new setpoint
        lcd.print("ok?   ");
      }
      lcd.setCursor(0,1);
      lcd.print("Set:");
      lcd.print(roundf(i_controller_setpoint()/1e3));
      lcd.print(" A FC:");
      lcd.print(roundf(i_fc/1000));
      lcd.print(" A  ");
      break;

    // Current page
    case PAGE_CURRENT:
      lcd.print("Current:         ");
      lcd.setCursor(0,1);
      lcd.print("Mot:");
      lcd.print(roundf(i_mot/1e3));
      lcd.print(" A Bat:");
      lcd.print(roundf(i_bat/1e3));
      lcd.print(" A ");
      break;

    // Voltage page
    case PAGE_VOLTAGE:
      lcd.print("Voltage:         ");
      lcd.setCursor(0,1);
      lcd.print("FC:");
      lcd.print(roundf(v_fc/1e3));
      lcd.print(" V Bat:");
      lcd.print(roundf(v_bat/1e3));
      lcd.print(" V  ");

      break;

    // Power page
    case PAGE_POWER:
      lcd.print("Power:           ");
      lcd.setCursor(0,1);
      lcd.print("FC:");
      lcd.print(roundf(pw_fc/1e3));
      lcd.print(" W Bat:");
      lcd.print(roundf(pw_bat/1e3));
      lcd.print(" W  ");

      break;

    // Temperature page
    case PAGE_TEMP:
      lcd.print("Temp: ");
      if (temp_fahrenheit) {
        lcd.print("to C?     ");
      } else {
        lcd.print("to F?     ");
      }
      lcd.setCursor(0,1);
      if (temp_fahrenheit) {
        lcd.print("Bat:");
        lcd.print((t_bat*9/5+32), 0);
        lcd.print("F Mot:");
        lcd.print((t_mot*9/5+32), 0);
        lcd.print("F ");
      } else {
        lcd.print("Bat:");
        lcd.print(t_bat, 0);
        lcd.print("C Mot:");
        lcd.print(t_mot, 0);
        lcd.print("C ");
      }
        break;

    // Hydrogen supply page
    case PAGE_HYDROGEN:
      lcd.print("H2:");
      lcd.print(m_h2);
      lcd.print(" g in tank  ");
      lcd.setCursor(0,1);
      lcd.print("P:");
      lcd.print(roundf(p_h2/100));
      lcd.print(" b T:");
      lcd.print(t_h2,1);
      lcd.print("C    ");
      break;

    // Stats page
    case PAGE_STATS:
      lcd.print("Stats:          ");
      lcd.setCursor(0,1);
      lcd.print("Up:");
      lcd.print((millis()/1000/60));
      lcd.print(" m Us:");
      lcd.print((prev_iter_time*100/ITER_INTERVAL));
      lcd.print("%    ");
      break;

    }
  }

  // SOC reset due?
  if (soc_reset_due) {

    // stop state of charge estimation
    soc_by_cc_stop();

    // switch everything off to minimize current
    fc_was_on = fc_on();
    if (fc_on()) solenoid_fc_toggle_wait();
    fan_motor_off();
    fan_battery_off();
    solenoid_contactor_off();
    delay(2000);

    // estimate soc by ocv and restart soc by cc
    soc_by_cc_start(soc_by_ocv(v_battery()));

    // switch everything back on
    solenoid_contactor_on();
    delay(500);
    lcd.begin(LCD_COLS, LCD_ROWS);
    if (!fc_on() && fc_was_on) solenoid_fc_toggle_wait();
    soc_reset_due = false;
  }

  // iteration end, save iteration time
  prev_iter_time = millis()-iter_start;

}
