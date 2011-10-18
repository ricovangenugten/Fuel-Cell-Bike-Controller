float i_bat_low_zero;
float i_bat_high_zero;
float i_fc_zero;
float i_motor_zero;

void i_reset() {
  i_bat_low_zero = read_average(I_BAT_LOW);
  i_bat_high_zero = read_average(I_BAT_HIGH);
  i_fc_zero = read_average(I_FC);
  i_motor_zero = read_average(I_MOTOR);
}

float i_battery_low() {
  return (read_average(I_BAT_LOW)-i_bat_low_zero)*I_BAT_LOW_C;
}

float i_battery_high() {
  return (read_average(I_BAT_HIGH)-i_bat_high_zero)*I_BAT_HIGH_C;
}

float i_fuel_cell() {
  return (read_average(I_FC)-i_fc_zero)*I_FC_C;
}

float i_motor() {
  return (read_average(I_MOTOR)-i_motor_zero)*I_MOTOR_C;
}
