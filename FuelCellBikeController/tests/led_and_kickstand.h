#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Kickstand test");
  digitalWrite(LED_WARNING, HIGH);
  delay(1000);
  digitalWrite(LED_WARNING, LOW);

}

int previousState = -1;
int state = -1;

void loop() {

  state = digitalRead(SW_KICKSTAND);

  if (state != previousState) {
    lcd.clear();
    if (state == LOW) {
      lcd.print("Kickstand in");
      digitalWrite(LED_WARNING, LOW);
    } else {
      lcd.print("Kickstand out");
      digitalWrite(LED_WARNING, HIGH);
    }
    previousState = state;
  }
  delay(1000);

}
