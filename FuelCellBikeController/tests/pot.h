#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Pot test");
  delay(500);
}

void loop() {

  lcd.clear();
  lcd.print("Pot value: ");
  lcd.print(pot_value());
  delay(500);

}
