#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Solenoid test");
  delay(1000);
}

void loop() {

  digitalWrite(MOTOR_SOLENOID, HIGH);
  lcd.clear();
  lcd.print("Motor solenoid on");
  delay(1000);

  digitalWrite(MOTOR_SOLENOID, LOW);
  lcd.clear();
  lcd.print("Motor solenoid off");
  delay(1000);

  digitalWrite(CONTACTOR_SOLENOID, HIGH);
  lcd.clear();
  lcd.print("Contactor solenoid on");
  delay(1000);

  digitalWrite(CONTACTOR_SOLENOID, LOW);
  lcd.clear();
  lcd.print("Contactor solenoid off");
  delay(1000);

}
