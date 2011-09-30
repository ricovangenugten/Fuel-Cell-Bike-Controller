float i_bat_low = 0;
float i_bat_high = 0;
float i_bat_low_zero = 0;
float i_bat_high_zero = 0;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Bat current test");
  delay(1000);

  i_bat_low_zero = read_average(I_BAT_LOW);
  i_bat_high_zero = read_average(I_BAT_HIGH);
}

void loop() {

  i_bat_low = (read_average(I_BAT_LOW)-i_bat_low_zero)*I_BAT_LOW_C;

  lcd.setCursor(0,0);
  lcd.print("Bat lo: ");
  lcd.print(i_bat_low, 3);
  lcd.print(" A");

  i_bat_high = (read_average(I_BAT_HIGH)-i_bat_high_zero)*I_BAT_HIGH_C;

  lcd.setCursor(0,1);
  lcd.print("Bat hi: ");
  lcd.print(i_bat_high, 3);
  lcd.print(" A");

}
