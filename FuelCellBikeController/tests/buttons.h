#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Button test");
  delay(1000);
}

void loop() {

  if(digitalRead(BUTTON_1) == LOW) {
    lcd.clear();
    lcd.print("Button 1 pushed");
  }
  if(digitalRead(BUTTON_2) == LOW) {
    lcd.clear();
    lcd.print("Button 2 pushed");
  }
  if(digitalRead(BUTTON_3) == LOW) {
    lcd.clear();
    lcd.print("Button 3 pushed");
  }
  if(digitalRead(BUTTON_4) == LOW) {
    lcd.clear();
    lcd.print("Button 4 pushed");
  }
  if(digitalRead(BUTTON_5) == LOW) {
    lcd.clear();
    lcd.print("Button 5 pushed");
  }

}
