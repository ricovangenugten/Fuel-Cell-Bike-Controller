float v_bat_zero;
float v_fc_zero;

void v_reset() {
  v_bat_zero = read_average(V_BAT);
  v_fc_zero = read_average(V_FC);
}

float v_battery() {
  return (read_average(V_BAT)-v_bat_zero)*V_BAT_C;
}

float v_fuel_cell() {
  return (read_average(V_FC)-v_fc_zero)*V_FC_C;
}
