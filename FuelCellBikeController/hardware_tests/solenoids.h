#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Solenoid test");
  delay(1000);
}

void loop() {

  digitalWrite(SOL_MOTOR, HIGH);
  lcd.clear();
  lcd.print("Motor solenoid on");
  delay(1000);

  digitalWrite(SOL_MOTOR, LOW);
  lcd.clear();
  lcd.print("Motor solenoid off");
  delay(1000);

  digitalWrite(SOL_CONTACT, HIGH);
  lcd.clear();
  lcd.print("Contactor solenoid on");
  delay(1000);

  digitalWrite(SOL_CONTACT, LOW);
  lcd.clear();
  lcd.print("Contactor solenoid off");
  delay(1000);

}
