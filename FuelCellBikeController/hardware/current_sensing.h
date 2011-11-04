int i_bat_low_zero;
int i_bat_high_zero;
int i_fc_zero;
int i_motor_zero;

void i_reset() {
  i_bat_low_zero = analogRead(I_BAT_LOW);
  i_bat_high_zero = analogRead(I_BAT_HIGH);
  i_fc_zero = analogRead(I_FC);
  i_motor_zero = analogRead(I_MOTOR);
}

int32_t i_battery_low() {
  return int32_t(analogRead(I_BAT_LOW)-i_bat_low_zero)*I_BAT_LOW_C;
}

int32_t i_battery_high() {
  return int32_t(analogRead(I_BAT_HIGH)-i_bat_high_zero)*I_BAT_HIGH_C;
}

int32_t i_battery() {
  int32_t i_bat_l = i_battery_low();
  if (i_bat_l < 15e4) {
    return i_bat_l;
  } else {
    return i_battery_high();
  }
}

int32_t i_fuel_cell() {
  return int32_t(analogRead(I_FC)-i_fc_zero)*I_FC_C;
}

int32_t i_motor() {
  return int32_t(analogRead(I_MOTOR)-i_motor_zero)*I_MOTOR_C;
}
