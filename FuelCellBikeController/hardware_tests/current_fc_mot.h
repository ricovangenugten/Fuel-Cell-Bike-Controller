float i_fc = 0;
float i_motor = 0;
float i_fc_zero = 0;
float i_motor_zero = 0;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("fc+mot curr test");
  delay(1000);

  i_fc_zero = read_average(I_FC);
  i_motor_zero = read_average(I_MOTOR);
}

void loop() {

  i_fc = (read_average(I_FC)-i_fc_zero)*I_FC_C;

  lcd.setCursor(0,0);
  lcd.print("FC:  ");
  lcd.print(i_fc, 3);
  lcd.print(" A    ");

  i_motor = (read_average(I_MOTOR)-i_motor_zero)*I_MOTOR_C;

  lcd.setCursor(0,1);
  lcd.print("Mot: ");
  lcd.print(i_motor, 3);
  lcd.print(" A    ");

}
