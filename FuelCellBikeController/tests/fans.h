#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Fan test");
  delay(1000);
}

void loop() {

  digitalWrite(FAN_BAT, HIGH);
  lcd.clear();
  lcd.print("Batt fan on");
  delay(10000);

  digitalWrite(FAN_BAT, LOW);
  lcd.clear();
  lcd.print("Batt fan off");
  delay(1000);

  digitalWrite(FAN_MOTOR, HIGH);
  lcd.clear();
  lcd.print("Motor fan on");
  delay(10000);

  digitalWrite(FAN_MOTOR, LOW);
  lcd.clear();
  lcd.print("Motor fan off");
  delay(1000);

}
