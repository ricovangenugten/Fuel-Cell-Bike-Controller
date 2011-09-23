float read_average (int pin) {
  float value = 0;
  for(int i=0;i<5;i++) {
    value += analogRead(pin);
    delay(100);
  }
  return value/5;
}
