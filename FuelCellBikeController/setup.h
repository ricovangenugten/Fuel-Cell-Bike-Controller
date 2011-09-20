#include "libraries/LiquidCrystal/LiquidCrystal.h"
#include "libraries/OneWire/OneWire.h"
#include "libraries/DallasTemperature/DallasTemperature.h"

LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//Temperature Sensors in battery
OneWire onewire(45);
DallasTemperature ds(&onewire);
//Temperature sensor in motor
OneWire motTemp(44);
DallasTemperature mt(&motTemp);
//Temperature sensor on tank
OneWire tankTemp(42);
DallasTemperature tt(&tankTemp);


void setup () {

  lcd.begin(16, 2);

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(BUTTON_4, INPUT);
  pinMode(BUTTON_5, INPUT);

  pinMode(BAT_FAN_ENABLE, OUTPUT);
  pinMode(MOT_FAN_ENABLE, OUTPUT);

  pinMode(MOTOR_SOLENOID, OUTPUT);
  pinMode(CONTACTOR_SOLENOID, OUTPUT);

  pinMode(BOOST_CONTROL, OUTPUT);

  lcd.print("UCD Hybrid Bike");
  delay(1000);

}
