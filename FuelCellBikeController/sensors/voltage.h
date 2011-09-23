float v_bat_zero;
float v_fc_zero;

void v_reset() {
  v_bat_zero = read_average(V_BAT_SENSOR);
  v_fc_zero = read_average(V_FC_SENSOR);
}

float v_battery() {
  return (read_average(V_BAT_SENSOR)-v_bat_zero)*V_BAT_CALIBRATION;
}

float v_fuel_cell() {
  return (read_average(V_FC_SENSOR)-v_fc_zero)*V_FC_CALIBRATION;
}
