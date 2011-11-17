int32_t v_battery() {
  return int32_t(analogRead(V_BAT)-V_BAT_ZERO)*V_BAT_C;
}

int32_t v_fuel_cell() {
  return int32_t(analogRead(V_FC)-V_FC_ZERO)*V_FC_C;
}
