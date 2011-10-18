float i_bat_l = 0;
float i_bat_h = 0;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Bat current test");
  delay(1000);
}

void loop() {

  i_bat_l = i_battery_low();
  lcd.setCursor(0,0);
  lcd.print("Bat lo: ");
  lcd.print(i_bat_l, 3);
  lcd.print(" A");

  i_bat_h = i_battery_high();
  lcd.setCursor(0,1);
  lcd.print("Bat hi: ");
  lcd.print(i_bat_h, 3);
  lcd.print(" A");

}
