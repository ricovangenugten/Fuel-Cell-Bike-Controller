float v_bat;
float v_fc;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {

  lcd.clear();
  lcd.print("Voltage sensing");
  delay(1000);

}

void loop() {

  v_bat = v_battery();

  lcd.setCursor(0,0);
  lcd.print("Bat: ");
  lcd.print(v_bat, 1);
  lcd.print(" volt   ");

  v_fc = v_fuel_cell();

  lcd.setCursor(0,1);
  lcd.print("Fc:  ");
  lcd.print(v_fc, 1);
  lcd.print(" volt    ");

}
