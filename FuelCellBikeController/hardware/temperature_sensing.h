//Temperature Sensors in battery
OneWire t_bat_onewire(T_BAT);
DallasTemperature dt_bat(&t_bat_onewire);

//Temperature sensor in motor
OneWire t_motor_onewire(T_MOTOR);
DallasTemperature dt_motor(&t_motor_onewire);

//Temperature sensor on tank
OneWire t_tank_onewire(T_TANK);
DallasTemperature dt_tank(&t_tank_onewire);

void t_request() {
  dt_bat.requestTemperatures();
  dt_motor.requestTemperatures();
  dt_tank.requestTemperatures();
}

int t_battery() {
  return roundf(dt_bat.getTempCByIndex(0));
}

int t_motor() {
  return roundf(dt_motor.getTempCByIndex(0));

}

int t_tank() {
  return roundf(dt_tank.getTempCByIndex(0));
}

void t_setup() {
  dt_bat.begin();
  dt_bat.setWaitForConversion(false);
  dt_motor.begin();
  dt_motor.setWaitForConversion(false);
  dt_tank.begin();
  dt_tank.setWaitForConversion(false);
}
