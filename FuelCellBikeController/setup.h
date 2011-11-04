void setup () {

  // setup lcd
  lcd.begin(16, 2);

  // setup temp sensors
  t_setup();

  // set output pins, the rest default to inputs
  pinMode(FAN_MOTOR,   OUTPUT);
  pinMode(FAN_BAT,     OUTPUT);
  pinMode(SOL_CONTACT, OUTPUT);
  pinMode(SOL_MOTOR,   OUTPUT);
  pinMode(I_CONTROL,   OUTPUT);
  pinMode(LED_WARNING, OUTPUT);

  // set pullup resistors
  digitalWrite(BUTTON_1, HIGH);
  digitalWrite(BUTTON_2, HIGH);
  digitalWrite(BUTTON_3, HIGH);
  digitalWrite(BUTTON_4, HIGH);
  digitalWrite(BUTTON_5, HIGH);
  digitalWrite(SW_KICKSTAND, HIGH);

  // reset voltage measurement
  v_reset();

  // reset current measurement
  i_reset();

  // setup current control output
  i_control_setup();

  // show message
  lcd.print("UCD Hybrid Bike ");

  /*
  lcd.setCursor(0,1);
  lcd.print("Estimating SOC..");
  delay(1000);

  // Initial SOC estimation
  soc_by_cc_start(soc_by_ocv(v_battery()));

  lcd.setCursor(0,1);
  lcd.print("Contactor on..  ");
  solenoid_contactor_on();
  delay(1000);

  lcd.setCursor(0,1);
  lcd.print("Motor ctrl on.. ");
  solenoid_motor_on();
  delay(1000);

  lcd.setCursor(0,1);
  lcd.print("Fans on..       ");
  fan_motor_on();
  fan_battery_on();
  */

}
