int32_t i_fc_set, i_controller_error_id = 0;

int i_controller(float i_fc) {

  int state = 0;
  float i_fc_error = 0;
  int i_fc_control_value;

  // do measurement and determine error
  i_fc_error = i_fc_set - i_fc;

  if (i_fc < 0.5) {
    i_controller_error_id = 1;
    return 0;
  }

  // calculate new control value
  i_fc_control_value += roundf(i_fc_error*I_CONTROLLER_P);

  // limit control value
  if (i_fc_control_value < 0) {
    i_controller_error_id = 1;
    i_fc_control_value = 0;
  }

  if (i_fc_control_value > 255) {
    i_controller_error_id = 2;
    i_fc_control_value = 255;
  }

  // output control value
  i_controller_error_id = 0;
  return i_fc_control_value;

}

void i_controller_set(long setpoint) {
  i_fc_set = setpoint;
}

int32_t i_controller_setpoint() {
  return i_fc_set;
}

int32_t i_controller_error() {
  return i_controller_error_id;
}
