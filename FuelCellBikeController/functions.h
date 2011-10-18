float read_average (int pin, bool high_impedance=true) {
  if (high_impedance) {
      analogRead(pin);
      delay(1);
  }
  float value = 0;
  for(int i=0;i<1;i++) {
    value += analogRead(pin);
    //delay(100);
  }
  return value;
}
