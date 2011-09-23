float bat_I = 0;
float bat_zero = 0;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Current sensing test");
  delay(1000);

  bat_zero = analogRead(BAT_I_SENSOR);
}

void loop() {

  bat_I = (analogRead(BAT_I_SENSOR)-bat_zero)*50/0.625;
  lcd.clear();
  lcd.print("Bat: ");
  lcd.print(bat_I, 3);
  lcd.print(" Amp");
  delay(1000);

}
