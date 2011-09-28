#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {

  lcd.clear();
  lcd.print("Temp test");
  delay(1000);

}

void loop() {

  lcd.clear();
  lcd.print("Tank: ");
  lcd.print(t_tank(), 0);
  lcd.print(" Bat: ");
  lcd.print(t_battery(), 0);
  lcd.setCursor(0,1);
  lcd.print("Motor: ");
  lcd.print(t_motor(), 0);
  delay(500);

}
