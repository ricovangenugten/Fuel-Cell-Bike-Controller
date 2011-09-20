#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Button test");
  delay(1000);
}

void loop() {

  if(digitalRead(BUTTON_1) == HIGH) {
    lcd.clear();
    lcd.print("Button 1 pushed");
    delay(1000);
    lcd.clear();
  }
  if(digitalRead(BUTTON_2) == HIGH) {
    lcd.clear();
    lcd.print("Button 2 pushed");
    delay(1000);
    lcd.clear();
  }
  if(digitalRead(BUTTON_3) == HIGH) {
    lcd.clear();
    lcd.print("Button 3 pushed");
    delay(1000);
    lcd.clear();
  }
  if(digitalRead(BUTTON_4) == HIGH) {
    lcd.clear();
    lcd.print("Button 4 pushed");
    delay(1000);
    lcd.clear();
  }
  /*if(digitalRead(BUTTON_5) == HIGH) {
    lcd.clear();
    lcd.print("Button 5 pushed");
    delay(1000);
  }*/

}
