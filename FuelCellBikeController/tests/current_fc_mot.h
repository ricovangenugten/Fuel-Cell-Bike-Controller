float i_fc = 0;
float i_mot = 0;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("fc+mot curr test");
  delay(1000);
}

void loop() {

  i_fc = i_fuel_cell();

  lcd.setCursor(0,0);
  lcd.print("FC:  ");
  lcd.print(i_fc/1e3, 1);
  lcd.print(" A ");
  lcd.print(analogRead(I_FC));
  lcd.print("  ");

  i_mot = i_motor();

  lcd.setCursor(0,1);
  lcd.print("Mot: ");
  lcd.print(i_mot/1e3, 1);
  lcd.print(" A ");
  lcd.print(analogRead(I_MOTOR));
  lcd.print("  ");

  delay(500);

}
