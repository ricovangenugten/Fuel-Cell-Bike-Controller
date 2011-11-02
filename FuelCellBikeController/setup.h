void setup () {

  // setup lcd
  lcd_setup();

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

  // show message and wait
  lcd_delay("UCD Hybrid Bike");

  // reset voltage measurement
  v_reset();

  // reset current measurement
  i_reset();

  // setup current control output
  i_control_setup();

}
