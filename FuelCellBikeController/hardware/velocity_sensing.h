uint32_t volatile vel_first_pulse_id, vel_last_meas_time, vel_total_pulse_count = 0;

void vel_pulse() {

  // increment total pulse count
  vel_total_pulse_count++;

  /*if (vel_first_pulse_time == 0) {
    vel_first_pulse_time = millis();
    vel_first_pulse_id = vel_total_pulse_count;
  }

  vel_last_pulse_time = millis();*/

}

void vel_begin() {
  attachInterrupt(4, vel_pulse, FALLING);
}

int vel_bike() {

  // pulses since last measurement
  int meas_pulses = vel_total_pulse_count-vel_first_pulse_id;

  // time since last measurement
  int meas_time = millis()-vel_last_meas_time;

  // reset measurement
  vel_last_meas_time = millis();

  // save next pulses id
  vel_first_pulse_id = vel_total_pulse_count+1;

  // return 0 if not enough pulses are counted
  if (meas_pulses < 2) return 0;

  // return velocity
  return meas_pulses*1e3/meas_time*VELOCITY_C; // mm / s

}

int32_t vel_bike_odo() {
  return roundf(vel_total_pulse_count*VELOCITY_C); // mm
}

void vel_bike_odo_reset() {
  vel_total_pulse_count = 0;
}

