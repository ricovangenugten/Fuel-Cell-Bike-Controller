#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {

  lcd.clear();
  lcd.print("Pressure test");
  delay(1000);

}

void loop() {

  lcd.clear();
  lcd.print("Tank: ");
  lcd.print(p_tank(), 3);
  delay(500);

}
