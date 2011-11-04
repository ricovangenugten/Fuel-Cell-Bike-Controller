float v_bat, v_fc = 0;
float p_bat, p_fc = 0;
float ocv_soc = 0;

float i_fc_set, i_fc = 0;

int display_page = 1;
int but_down = 0;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("I control test");
  delay(500);
}

void loop() {

  // change display page if button is down
  but_down = button_down();
  if (but_down > 0) {
      display_page = but_down;
  }

  // setpoint 0-50 A via potmeter
  i_controller_set((pot_value()*50)/1024);

  // output to LCD
  lcd.clear();
  switch (display_page) {

  case 1:
    lcd.print(lcd_line_1);
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


