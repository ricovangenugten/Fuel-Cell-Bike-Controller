#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("PWM test");
  delay(500);

}

void loop() {

  for (int i=0;i<256;i++) {
    i_control_value(i);
    delayMicroseconds(pot_value());
  }
  for (int i=255;i>=0;i--) {
    i_control_value(i);
    delayMicroseconds(pot_value());
  }

}


