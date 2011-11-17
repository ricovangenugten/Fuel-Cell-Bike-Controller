int32_t i_battery_low() {
  return int32_t(analogRead(I_BAT_LOW)-I_BAT_LOW_ZERO)*I_BAT_LOW_C;
}

int32_t i_battery_high() {
  return int32_t(analogRead(I_BAT_HIGH)-I_BAT_HIGH_ZERO)*I_BAT_HIGH_C;
}

int32_t i_battery() {
  int32_t i_bat_l = i_battery_low();
  if (i_bat_l < I_BAT_CROSSOVER) {
    return i_bat_l;
  } else {
    return i_battery_high();
  }
}

int32_t i_fuel_cell() {
  return int32_t(analogRead(I_FC)-I_FC_ZERO)*I_FC_C;
}

int32_t i_motor() {
  return int32_t(analogRead(I_MOTOR)-I_MOTOR_ZERO)*I_MOTOR_C;
}
