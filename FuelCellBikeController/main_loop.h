uint32_t timestamp, id, iter_start;
int32_t soc_charge, i_fc_setpoint, i_fc, i_bat, i_mot, v_fc, v_bat, pw_fc, pw_bat, pw_mot, p_h2, m_h2 = 0;
int prev_iter_time, iter_usage, t_bat, t_mot, t_h2 = 0;
bool soc_reset_due;

void loop() {

  // SOC reset due?
  if (soc_reset_due) {
    soc_by_cc_stop();
    solenoid_motor_off();
    fan_motor_off();
    fan_battery_off();
    delay(500);
    solenoid_contactor_off();
    delay(500);
    soc_by_cc_start(soc_by_ocv(v_battery()));
    solenoid_contactor_on();
    delay(500);
    solenoid_motor_on();
    fan_motor_on();
    fan_battery_on();
    soc_reset_due = false;
  }

  // request temperatures
  // a delay is needed before the values can be fetched, therefore this is done before the wait
  t_request();

  // save iteration time
  if (iter_start > 0) {
    prev_iter_time = millis()-iter_start;
  }

  // wait for button presses until start of next iteration
  while (millis() % ITER_INTERVAL) {

    switch (button_down()) {
    case 1: // action button
      // when in daq menu page
      if (menu_page() == 1) {
        // if daq is turned off
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
      }
      // when in soc menu page
      if (menu_page() == 3 && !daq_on()) {
        soc_reset_due = true;
      }
      menu_refresh_due_now();
      break;
    case 2:
      menu_prev();
      break;
    case 3:
      menu_next();
      break;
    }
  }

  // Start iteration
  iter_start = millis();

  // SOC
  soc_charge = soc_by_cc();

  // Get FC current setpoint
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

  // Temperature measurements
  t_h2 = t_tank();
  //t_bat = t_battery();
  //t_mot = t_motor();

  // Pressure measurement
  p_h2 = p_tank();

  // Hydrogen mass estimation
  m_h2 = 0;

  // if data acquisition is on, save data to sd card
  if (daq_on()) {

    timestamp = daq_measurement_start();
    id = daq_measurement_id();

    // header
    if (id == 0) {
      // Stats
      sd_bw.putStr("id");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("timestamp (ms)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("prev iter time (ms)");
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
      sd_bw.putStr("t_bat (deg C)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("t_mot (deg C)");
      // Hydrogen supply
      sd_bw.putStr("p_h2 (kPa)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      sd_bw.putStr("m_h2 (g)");
      sd_bw.putStr(DAQ_CSV_SEPARATOR);
      // Line end
      sd_bw.putStr("\r\n");
      sd_bw.writeBuf();
    }

    // write measurement
    // Stats
    sd_bw.putNum(id);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(timestamp);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(prev_iter_time);
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
    sd_bw.putNum(t_h2);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(t_bat);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(t_mot);
    // Hydrogen supply
    sd_bw.putNum(p_h2);
    sd_bw.putStr(DAQ_CSV_SEPARATOR);
    sd_bw.putNum(m_h2);
    // Line end
    sd_bw.putStr("\r\n");
    sd_bw.writeBuf();

    daq_measurement_end();
  }

  // setpoint 0-50e3 mA via potmeter
  i_controller_set(uint16_t(pot_value())*49);

  // output current control value
  i_control_output(i_controller(i_fc));

  // menu refresh due?
  if (menu_refresh_due()) {

    // output menu
    lcd.setCursor(0,0);
    switch (menu_page()) {

    // Data Acquisition
    case 1:
      lcd.print("Daq: ");
      if (!daq_on()) {
        lcd.print("Start?     ");
      } else {
        lcd.print("Stop?      ");
      }
      lcd.setCursor(0,1);
      switch (sd_error()) {
        case 0:
          lcd.print("                ");
          lcd.setCursor(0,1);
          lcd.print(sd_file_name);
          break;
        case 1:
          lcd.print("SD init error   ");
          break;
        case 2:
          lcd.print("SD open error   ");
          break;
        }
      break;

    // Stats
    case 2:
      lcd.print("Stats:          ");
      lcd.setCursor(0,1);
      lcd.print("Up:");
      lcd.print((millis()/1000/60));
      lcd.print(" m Us:");
      lcd.print((prev_iter_time*100/ITER_INTERVAL));
      lcd.print("%    ");
      break;

    // SOC estimation
    case 3:
      lcd.print("SOC: ");
      if (soc_reset_due) {
        lcd.print(" Estimating ");
      } else if (!daq_on()) {
        lcd.print(" Reset?    ");
      } else {
        lcd.print(" (daq on)  ");
      }
      lcd.setCursor(0,1);
      if (soc_reset_due) {
        lcd.print("                ");
      } else {
        lcd.print(soc_init_val());
        lcd.print(" ");
        lcd.print(soc_percentage(soc_init_val()));
        lcd.print("% ");
        lcd.print(soc_by_cc());
        lcd.print(" ");
        lcd.print(soc_percentage(soc_by_cc()));
        lcd.print("% ");
      }
      break;

    // Current control
    case 4:
      lcd.print("Cur ctrl: ");
      switch (i_controller_error()) {
      case 0:
        lcd.print("ok    ");
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
      lcd.setCursor(0,1);
      lcd.print("Set:");
      lcd.print(roundf(i_controller_setpoint()/1e3));
      lcd.print(" A FC:");
      lcd.print(roundf(i_fc/1000));
      lcd.print(" A  ");
      break;

    // Current measurements
    case 5:
      lcd.print("Current:         ");
      lcd.setCursor(0,1);
      lcd.print("Mot:");
      lcd.print(roundf(i_mot/1000));
      lcd.print(" A Bat:");
      lcd.print(roundf(i_bat/1000));
      lcd.print(" A ");
      break;

    // Voltage measurements
    case 6:
      lcd.print("Voltage:         ");
      lcd.setCursor(0,1);
      lcd.print("FC:");
      lcd.print(roundf(v_fc/1000));
      lcd.print(" V Bat:");
      lcd.print(roundf(v_bat/1000));
      lcd.print(" V");

      break;

    // Power estimations
    case 7:
      lcd.print("Power:           ");
      lcd.setCursor(0,1);
      lcd.print("FC:");
      lcd.print(roundf(pw_fc/1e3));
      lcd.print(" W Bat:");
      lcd.print(roundf(pw_bat/1e3));
      lcd.print(" W  ");

      break;

    // Temperature measurements
    case 8:
      lcd.print("Temp bat:");
      lcd.print(t_bat);
      lcd.print(" C");
      lcd.setCursor(0,1);
      lcd.print("Temp Mot:");
      lcd.print(t_mot);
      lcd.print(" C");
      break;

    // Hydrogen supply
    case 9:
      lcd.print("H2: ");
      if (daq_on()) {
        lcd.print(m_h2);
        lcd.print(" g used    ");
      } else {
        lcd.print("(start daq)");
      }
      lcd.setCursor(0,1);
      lcd.print("P:");
      lcd.print(roundf(p_h2/100));
      lcd.print(" b T:");
      lcd.print(t_h2);
      lcd.print(" C ");
      break;

    }
  }

}
