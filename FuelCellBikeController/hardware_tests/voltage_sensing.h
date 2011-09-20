float bat_v = 0;
float fc_v = 0;
float bat_zero = 0;
float fc_zero = 0;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Voltage sensing test");
  delay(1000);

  bat_zero = analogRead(BAT_V_SENSOR);
  fc_zero = analogRead(FC_V_SENSOR);
}

void loop() {

  bat_v = (analogRead(BAT_V_SENSOR)-bat_zero)/2.25;
  lcd.clear();
  lcd.print("Bat: ");
  lcd.print(bat_v, 3);
  lcd.print(" volt");
  delay(1000);

  fc_v = (analogRead(FC_V_SENSOR)-fc_zero)/2.25;
  lcd.clear();
  lcd.print("Fc: ");
  lcd.print(fc_v, 3);
  lcd.print(" volt");
  delay(1000);

}
