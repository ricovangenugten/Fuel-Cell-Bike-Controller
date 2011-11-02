LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

char lcd_line_1[17];
char lcd_line_2[17];

void lcd_setup() {
  lcd.begin(16, 2);
}

void lcd_upper(char line_1[17]) {
  strcpy(lcd_line_1, line_1);
}

void lcd_lower(char line_2[17]) {
  strcpy(lcd_line_2, line_2);
}

void lcd_message(char message[17]) {
  lcd_upper(message);
}

void lcd_draw() {
  lcd.clear();
  lcd.print(lcd_line_1);
  lcd.setCursor(0,1);
  lcd.print(lcd_line_2);
}

void lcd_delay(char message[17]) {
  lcd_message(message);
  lcd_draw();
  delay(500);
}
