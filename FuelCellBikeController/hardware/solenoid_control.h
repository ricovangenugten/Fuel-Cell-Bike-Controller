void solenoid_motor_on() {
  digitalWrite(SOL_MOTOR, HIGH);
}

void solenoid_motor_off() {
  digitalWrite(SOL_MOTOR, LOW);
}

void solenoid_contactor_on() {
  digitalWrite(SOL_CONTACT, HIGH);
}

void solenoid_contactor_off() {
  digitalWrite(SOL_CONTACT, LOW);
}
