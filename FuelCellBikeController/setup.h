void setup () {

  // set output pins, the rest default to inputs
  pinMode(FAN_MOTOR,   OUTPUT);
  pinMode(FAN_BAT,     OUTPUT);
  pinMode(SOL_CONTACT, OUTPUT);
  pinMode(SOL_MOTOR,   OUTPUT);
  pinMode(SOL_FC,      OUTPUT);
  pinMode(I_CONTROL,   OUTPUT);
  pinMode(LED_WARNING, OUTPUT);

  // set pullup resistors
  digitalWrite(BUTTON_1, HIGH);
  digitalWrite(BUTTON_2, HIGH);
  digitalWrite(BUTTON_3, HIGH);
  digitalWrite(BUTTON_4, HIGH);
  digitalWrite(BUTTON_5, HIGH);
  digitalWrite(SW_KICKSTAND, HIGH);

  // setup lcd
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.print("UCD Hybrid Bike ");
  delay(1000);

  // setup temp sensors
  t_setup();

  // setup current control output
  i_control_setup();

  lcd.setCursor(0,1);
  lcd.print("Estimating SOC..");
  delay(1000);

  // Initial SOC estimation
  soc_by_cc_start(soc_by_ocv(v_battery()));

  solenoid_contactor_on();
  delay(100);
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.setCursor(0,1);
  lcd.print("Contactor on..  ");
  delay(900);

  lcd.setCursor(0,1);
  lcd.print("FC ctrl on..    ");
  if (!fc_on()) solenoid_fc_toggle_wait();

  // start velocity measurement
  vel_begin();

}
