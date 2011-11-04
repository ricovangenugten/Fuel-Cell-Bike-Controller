int v_bat_zero;
int v_fc_zero;

void v_reset() {
  v_bat_zero = analogRead(V_BAT);
  v_fc_zero = analogRead(V_FC);
}

int32_t v_battery() {
  return int32_t(analogRead(V_BAT)-v_bat_zero)*V_BAT_C;
}

int32_t v_fuel_cell() {
  return int32_t(analogRead(V_FC)-v_fc_zero)*V_FC_C;
}
