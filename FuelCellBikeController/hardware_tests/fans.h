#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Fan test");
  delay(1000);
}

void loop() {

  digitalWrite(BAT_FAN_ENABLE, HIGH);
  lcd.clear();
  lcd.print("Batt fan on");
  delay(10000);

  digitalWrite(BAT_FAN_ENABLE, LOW);
  lcd.clear();
  lcd.print("Batt fan off");
  delay(1000);

  digitalWrite(MOT_FAN_ENABLE, HIGH);
  lcd.clear();
  lcd.print("Motor fan on");
  delay(10000);

  digitalWrite(MOT_FAN_ENABLE, LOW);
  lcd.clear();
  lcd.print("Motor fan off");
  delay(1000);

}
