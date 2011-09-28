float i_bat = 0;
float i_bat_zero = 0;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Current sensing test");
  delay(1000);

  i_bat_zero = analogRead(I_BAT);
}

void loop() {

  i_bat = (analogRead(I_BAT)-i_bat_zero)*5/1023*50/0.625;
  lcd.clear();
  lcd.print("Bat: ");
  lcd.print(i_bat, 3);
  lcd.print(" Amp");
  delay(1000);

}
