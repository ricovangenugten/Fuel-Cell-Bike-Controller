int volatile vel_pulse_count = 0;
uint32_t volatile vel_first_pulse_time, vel_last_pulse_time, vel_total_pulse_count = 0;
bool volatile vel_reset_due = true;

void vel_pulse() {

  // save pulse time
  vel_last_pulse_time = millis();

  // reset due?
  if (vel_reset_due) {
    // reset measurement
    vel_first_pulse_time = vel_last_pulse_time;
    vel_pulse_count = 1;
    vel_reset_due = false;
  } else {
    // increment pulse count
    vel_pulse_count++;
  }

  // increment total pulse count
  vel_total_pulse_count++;

}

void vel_begin() {
  vel_reset_due = true;
  attachInterrupt(2, vel_pulse, RISING);
}

int vel_bike() {

  // return 0 if not enough pulses are counted
  if (vel_reset_due || vel_pulse_count < 2) return 0;

  // save pulse count and time
  int meas_periods = vel_pulse_count-1;
  int meas_time = vel_last_pulse_time-vel_first_pulse_time;

  // reset pulse count and time
  vel_reset_due = true;

  // return velocity
  return meas_periods*1e3/meas_time*VELOCITY_C; // mm / s

}

int32_t vel_bike_odo() {
  return roundf(vel_total_pulse_count*VELOCITY_C/1e3); // m
}

void vel_bike_odo_reset() {
  vel_total_pulse_count = 0;
}

