float capacity = 0;
float soc = 0;
float v_bat = 0;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("soc ocv test");
  delay(1000);
}

void loop() {

  v_bat = v_battery();
  capacity = ocv_capacity(v_bat);
  soc = ocv_capacity_to_soc(capacity);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("v_bat: ");
  lcd.print(v_bat);

  lcd.setCursor(0,1);
  lcd.print(soc,0);
  lcd.print("% ");
  lcd.print(capacity,0);
  lcd.print(" mAh");

}


