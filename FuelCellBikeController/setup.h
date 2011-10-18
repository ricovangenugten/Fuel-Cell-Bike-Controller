LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup () {

  // start LCD
  lcd.begin(16, 2);

  // start temp sensors
  t_begin();

  // set output pins, the rest default to inputs
  pinMode(FAN_MOTOR,   OUTPUT);
  pinMode(FAN_BAT,     OUTPUT);
  pinMode(SOL_CONTACT, OUTPUT);
  pinMode(SOL_MOTOR,   OUTPUT);
  pinMode(I_CONTROL,  OUTPUT);
  pinMode(LED_WARNING, OUTPUT);

  // set pullup resistors
  digitalWrite(BUTTON_1, HIGH);
  digitalWrite(BUTTON_2, HIGH);
  digitalWrite(BUTTON_3, HIGH);
  digitalWrite(BUTTON_4, HIGH);
  digitalWrite(BUTTON_5, HIGH);
  digitalWrite(SW_KICKSTAND, HIGH);

  lcd.print("UCD Hybrid Bike");
  delay(1000);

  // reset voltage measurement
  v_reset();

  // reset current measurement
  i_reset();

  // setup current control output
  i_control_setup();

}
