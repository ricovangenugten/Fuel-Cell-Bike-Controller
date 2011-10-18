long time;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("Timer testing");
  delay(1000);

}

void loop(){
  lcd.clear();
  lcd.print("Time: ");
  time = millis();
  //prints time since program started
  lcd.print(time);
  lcd.print(" ms");
  // wait a second so as not to send massive amounts of data
  delay(1000);
}

