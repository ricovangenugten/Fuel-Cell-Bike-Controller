unsigned long daq_start_time = 0;
unsigned long daq_measurement_id_val = 0;
unsigned long daq_measurement_start_time = 0;
int daq_state = 0;
int daq_measurement_time = 0;

bool daq_start() {
  daq_state = 1;
  return true;
}

bool daq_stop() {
  daq_state = 0;
  daq_start_time = 0;
  daq_measurement_id_val = 0;
  return true;
}

bool daq_on() {
  return (daq_state == 1);
}

unsigned long daq_measurement_start() {

  // save start time
  daq_measurement_start_time = millis();
  // save measurement start if not already set
  if (daq_start_time == 0) daq_start_time = daq_measurement_start_time;
  return (daq_measurement_start_time-daq_start_time);

}

unsigned long daq_measurement_id() {
  return daq_measurement_id_val;
}

bool daq_measurement_end() {

  // increment measurement id
  daq_measurement_id_val++;

  // calculate (approximate) cpu usage
  daq_measurement_time = (millis()-daq_measurement_start_time);

  return true;

}

int daq_last_measurement_time() {
  return daq_measurement_time;
}

