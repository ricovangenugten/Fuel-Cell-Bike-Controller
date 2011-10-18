float v_bat, v_fc = 0;
float p_bat, p_fc = 0;
float ocv_soc = 0;

float i_fc_set, i_fc_error, i_fc = 0;
int i_fc_control_value = 0;
int state = 0;

int display_page = 1;
int but_down = 0;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("PWM test");
  delay(500);
}

void loop() {

  // change display page if button is down
  but_down = button_down();
  if (but_down > 0) {
      display_page = but_down;
  }

  // measure voltages
  v_bat = v_battery();
  v_fc = v_fuel_cell();

  // estimate OCV SOC
  ocv_soc = ocv_capacity_to_soc(ocv_capacity(v_fc));

  // no state yet
  state = 0;

  // setpoint 0-50 A via potmeter
  i_fc_set = (pot_value()*50)/1024;

  // do measurement and determine error
  i_fc = i_fuel_cell();
  i_fc_error = i_fc_set - i_fc;

  if (i_fc < 0.5) {
    i_fc_control_value = 0;
    state = 1;
  }

  // still no error?
  if (state == 0) {

    // calculate new control value
    i_fc_control_value += roundf(i_fc_error*I_CONTROLLER_P);

    // limit control value
    if (i_fc_control_value > 255) {
      i_fc_control_value = 255;
      state = 2;
    }
    if (i_fc_control_value < 0) {
      i_fc_control_value = 0;
      state = 3;
    }

    // output control value
    i_control_output(i_fc_control_value);

  }

  // power estimation
  p_fc = v_fc * i_fc;

  // output to LCD
  lcd.clear();
  switch (display_page) {

  case 1:
    if (state == 0) lcd.print("Current control");
    if (state == 1) lcd.print("I control: no in");
    if (state == 2) lcd.print("I control: high out");
    if (state == 3) lcd.print("I control: low out");
    lcd.setCursor(0,1);
    lcd.print("S:");
    lcd.print(i_fc_set, 1);
    lcd.print(" A M:");
    lcd.print(i_fc, 1);
    lcd.print(" A");

    break;

  case 2:
    lcd.print("Voltage");
    lcd.setCursor(0,1);
    lcd.print("FC:");
    lcd.print(v_fc, 0);
    lcd.print(" V Bt:");
    lcd.print(v_bat, 0);
    lcd.print(" V");
    break;

  case 3:
    lcd.print("State of Charge");
    lcd.setCursor(0,1);
    lcd.print("SOC OCV:");
    lcd.print(ocv_soc, 0);
    break;

  case 4:
    lcd.print("Power");
    lcd.setCursor(0,1);
    lcd.print("FC:");
    lcd.print(p_fc, 0);
    lcd.print(" W Bt:");
    lcd.print(p_bat, 0);
    lcd.print(" W");
    break;

  case 5:
    lcd.print("Dikke shit!");
    break;
  }

  // wait for a while
  delay(300);
}


