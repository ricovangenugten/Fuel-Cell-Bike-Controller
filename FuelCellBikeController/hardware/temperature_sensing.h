//Temperature Sensors in battery
OneWire t_bat_onewire(T_BAT);
DallasTemperature dt_bat(&t_bat_onewire);
//Temperature sensor in motor
OneWire t_motor_onewire(T_MOTOR);
DallasTemperature dt_motor(&t_motor_onewire);
//Temperature sensor on tank
OneWire t_tank_onewire(T_TANK);
DallasTemperature dt_tank(&t_tank_onewire);

float t_battery() {
  dt_bat.requestTemperatures();
  return dt_bat.getTempCByIndex(0);
}

float t_motor() {
  dt_motor.requestTemperatures();
  return dt_motor.getTempCByIndex(0);

}

float t_tank() {
  dt_tank.requestTemperatures();
  return dt_tank.getTempCByIndex(0);
}

void t_setup() {
  dt_bat.begin();
  dt_motor.begin();
  dt_tank.begin();
}
