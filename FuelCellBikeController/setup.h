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
  pinMode(BC_I_LIMIT,  OUTPUT);

  // reset voltage sensors

  lcd.print("UCD Hybrid Bike");
  delay(1000);

  // reset voltage sensors
  v_reset();

}
