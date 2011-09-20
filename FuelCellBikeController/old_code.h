#include <avr/pgmspace.h>
#include <math.h>
#include "libraries/EEPROM/EEPROM.h"
#include "libraries/OneWire/OneWire.h"
#include "libraries/DallasTemperature/DallasTemperature.h"
#include "libraries/LiquidCrystal/LiquidCrystal.h"

//Initial Mass of Hydrogen - Theoretical Maximum
PROGMEM float hydMaxMass = .1669; //kilograms

//Temperature Addresses
//Level 1: 28F5F02503000034
//Level 2: 284FE825030000BE
//Level 3: 28D92926030000DA
//Level 4: 28E91C2603000061
//Level 5: 286F0A26030000D9
//tanktemp : find
//motortemp : find

//Button Declarations
//  __________________________
// |                          |
// |   (6) (5) (8) (7) (9)    |
// |   ____________________   |
// |  |____________________|  |
// |                          |
// |__________________________|

int battFanOn = 0;
int motFanOn = 0;

int i;
//Fuel Cell Power Curve
PROGMEM int Current[18] = {4, 8, 11, 15, 18, 22, 25, 28, 32, 35, 37, 41, 44, 48, 51, 55, 58, 62};
PROGMEM int Power[18] = {129, 275, 422, 551, 697, 826, 936, 1060, 1170, 1270, 1360, 1450, 1560, 1650, 1750, 1840, 1910, 1970};

//Hydrogen Constants
PROGMEM float P_Sens_Prop = 617.5;
PROGMEM float Convert_To_kPa = 6.894;
float tanksoc = 0;

int pwmCurrent;
int pwmVoltage;

//Battery Constants
PROGMEM float battVoltConstant = .625;
PROGMEM int currNomHass200 = 200;
PROGMEM float voltRefHass200 = 2.5;
PROGMEM float amphr_initial = 25; // Amp-Hr in fully chaarged battery pack

//Motor Current Constants
PROGMEM float motVoltConstant = .625;
//PROGMEM int currNomHass200 = 200; //same as battery
//PROGMEM float voltRefHass200; //same as battery
float powerDemand;
//batt mot hass200

float batt_avg_temp;
int state;
int prev_state;
int reset_started;

PROGMEM float Analog_Digital_Constant = .0049;  //Internal DAC ratio
PROGMEM float Digital_Analog_Constant = 51.2; //External DAC for boost converter

int fanState;

//Battery Current
int battCurrent;
int battCurrentDig = 0;
float battCurrentScaled = 0;
float battCurrentCalc = 0;
int battVoltageMeasured;
float battsoc = 0;

//FuelCell Current
int fcCurrent;
int fcCurrentDig = 0;
float fcCurrentScaled = 0;
float fcCurrentCalc = 0;


//Motor Current
int motCurrent;
int motCurrentDig = 0;
float motCurrentScaled = 0;
float motCurrentCalc = 0;

//Auxilliary Current
int auxCurrent;
int auxCurrentDig = 0;
float auxCurrentScaled = 0;
float auxCurrentCalc = 0;

float sumOfCurrents = 0;

float volumeOfTanks = 11.9; //Liter volume tanks
float Rbar = 4.124; //R constant for hydrogen

float hydMassInst = 0; //instantaneous mass of hydrogen tanks
float tempOfTanks = 0;


//LCD
PROGMEM int LCDRS = 2;
PROGMEM int LCDEN = 3;
PROGMEM int LCDD4 = 9;
PROGMEM int LCDD5 = 10;
PROGMEM int LCDD6 = 11;
PROGMEM int LCDD7 = 12;
int printChoice = 0;
int prev_printChoice = 0;
int buttonPushed = 0;
int printed = 0;

unsigned long timer;
unsigned long timer_prev;
unsigned long reset_timer;
unsigned long reset_timer_prev;
unsigned long lcd_timer = 0;;
unsigned long lcd_timer_prev = 0;


//LiquidCrystal lcd(LCDRS, LCDEN, LCDD4, LCDD5, LCDD6, LCDD7);
//LiquidCrystal lcd(2, 3, 9, 10, 11, 12);
LiquidCrystal lcd (53, 51, 46, 47, 48, 49);


//Temperature Sensors in battery
OneWire onewire(45);
DallasTemperature ds(&onewire);
//Temperature sensor in motor
OneWire motTemp(44);
DallasTemperature mt(&motTemp);
//Temperature sensor on tank
OneWire tankTemp(42);
DallasTemperature tt(&tankTemp);



/////////////////////////////////////////////
//VARIABLES
/////////////////////////////////////////////

  //Hydrogen
  float hydrogen_pressure = 0;
  float hydrogen_pressure_act = 0;
  float hydrogen_pressure_kpa = 0;
  int hydPressureDig = 0;
  int hydPressure = 0;
  int EE_hydrogen_pressure_kpa_addr = 0;

  //Battery
  float ampHourBatt = 0;
  float ampHourBatt_temp = 0;
  int EE_batt_amp_hour_addr = 1;

  float boostConverterCurrent_float = 0;
  int boostConverterCurrent = 0;
  boolean DAC0 = false;
  int DACpin0 = 0;
  boolean DAC1 = false;
  int DACpin1 = 0;
  boolean DAC2 = false;
  int DACpin2 = 0;
  boolean DAC3 = false;
  int DACpin3 = 0;
  boolean DAC4 = false;
  int DACpin4 = 0;
  boolean DAC5 = false;
  int DACpin5 = 0;
  boolean DAC6 = false;
  int DACpin6 = 0;
  boolean DAC7 = false;
  int DACpin7 = 0;

  //Temperatures
  float level1_C = 0;
  float level2_C = 0;
  float level3_C = 0;
  float level4_C = 0;
  float level5_C = 0;
  float tanktemp = 0;
  float motortemp = 0;

  //


void setup () {
  Serial.begin(9600); //declare 9600 baudrate for programming
  lcd.begin(16, 2);
  ds.begin();
  mt.begin();
  tt.begin();

  pinMode(5, INPUT); //button 2
  pinMode(6, INPUT); //button 1
  pinMode(7, INPUT); //button4
  pinMode(8, INPUT); //button3
  pinMode(9, INPUT); //button5

  pinMode(34, OUTPUT); //batt fan
  pinMode(32, OUTPUT); //mot fan
  pinMode(52, OUTPUT); //motor enable
  pinMode(36, OUTPUT); //contactor

  pinMode(11, OUTPUT); //pwm for zahn

  hydrogen_pressure_kpa = EEPROM.read(EE_hydrogen_pressure_kpa_addr);
  ampHourBatt = EEPROM.read(EE_batt_amp_hour_addr);

  state = 0; //initial state of 0 -- set tank pressure/initial batt charge
  prev_state = 0;
  timer_prev = 0;
  lcd.print("Aaron Test");
  printed = 1;
  ampHourBatt = amphr_initial;
  fanState = 0;

}

void loop() {
  /*
  if (state == 0) {
    if (OK_Pushed){
      if (First_Push){
        Second_Push = millis();
        Time_Held = Second_Push - First_Push;
        if (Time_Held >= 5000) {
          state = 1;
        }
      }
      else {

      }
    }
  }
  */
  //else if (state == 1) {
  //Conversion to find pressure of Hydrogen tank
  battsoc = (ampHourBatt/amphr_initial)*100; // calculate battery SOC

  if (battsoc < 20) {
  //No longer in valid range of operation
      state = 2;
      digitalWrite(52, LOW);
      digitalWrite(36, LOW);

      if (prev_state != state)
      {
        reset_timer_prev = reset_timer;
        lcd.clear();
        lcd.print("Batt. below 20%");
        lcd.setCursor(1,2);
        lcd.print("Hld Blk Btns RST");
      }
    prev_state = state;

      if (digitalRead(6) == HIGH) {
        if (digitalRead(5) == HIGH) {
          reset_timer = millis();
          if (reset_started == 0) {
            reset_timer_prev = reset_timer;
            reset_started = 1;
          }
          if (reset_timer - reset_timer_prev > 3000) {
            ampHourBatt = amphr_initial;
          }

        }
        else reset_started = 0;
      }
     else reset_started = 0;
  }
  else{

  digitalWrite(52, HIGH);
  digitalWrite(36, HIGH);

  hydPressureDig = analogRead(hydPressure);
  hydrogen_pressure = (float)hydPressureDig*Analog_Digital_Constant;
  hydrogen_pressure_act = hydrogen_pressure*P_Sens_Prop;
  hydrogen_pressure_kpa = Convert_To_kPa*hydrogen_pressure_act;
  EEPROM.write(EE_hydrogen_pressure_kpa_addr, hydrogen_pressure_kpa);

  //Calculate current mass of hydrogen in tanks
  hydMassInst = hydrogen_pressure_kpa*volumeOfTanks/tempOfTanks/Rbar;


  //Temperature Sensors
  ds.requestTemperatures();
  /*
  //Level 1
  level1_C = ds.getTempC((DeviceAddress){0x28,0xF5,0xF0,0x25,0x03,0x00,0x00,0x34});
  //Level 2
  level2_C = ds.getTempC((DeviceAddress){0x28,0x4F,0xE8,0x25,0x03,0x00,0x00,0xBE});
  //Level 3
  level3_C = ds.getTempC((DeviceAddress){0x28,0xD9,0x29,0x26,0x03,0x00,0x00,0xDA});
  //Level 4
  level4_C = ds.getTempC((DeviceAddress){0x28,0xE9,0x1C,0x26,0x03,0x00,0x00,0x61});
  //Level 5
  level5_C = ds.getTempC((DeviceAddress){0x28,0x6F,0x0A,0x26,0x03,0x00,0x00,0xD9});
  */
  level1_C = ds.getTempCByIndex(0);
  level2_C = ds.getTempCByIndex(1);
  level3_C = ds.getTempCByIndex(2);
  level4_C = ds.getTempCByIndex(3);
  level5_C = ds.getTempCByIndex(4);
  /*
  Serial.println(level1_C);
  Serial.println(level2_C);
  Serial.println(level3_C);
  Serial.println(level4_C);
  Serial.println(level5_C);
  */

  tt.requestTemperatures();
  tanktemp = tt.getTempCByIndex(0); //not actual address
  //motortemp
  mt.requestTemperatures();
  motortemp = mt.getTempCByIndex(0);//not actual address
  batt_avg_temp = (level1_C+level2_C+level3_C+level4_C+level5_C)/5;

  if (battFanOn == 0){
    if (level1_C > 60) {
      digitalWrite(34, HIGH);
    }
    else if (level2_C > 60) {
      digitalWrite(34, HIGH);
    }
    else if (level3_C > 60) {
      digitalWrite(34, HIGH);
    }
    else if (level4_C > 60) {
      digitalWrite(34, HIGH);
    }
    else if (level5_C > 60) {
      digitalWrite(34, HIGH);
    }
  battFanOn = 1;
  }
  else{
    if (level1_C < 50){
      if (level2_C < 50) {
        if (level3_C < 50) {
          if (level4_C < 50) {
            if (level5_C < 50) {
              battFanOn = 0;
              digitalWrite(34, LOW);
            }
          }
        }
      }
    }

  }

  if (motFanOn == 0) {
    if (motortemp > 50) {
      motFanOn = 1;
      digitalWrite(32, HIGH);
    }
  }
  else {
    if (motortemp < 40) {
      motFanOn = 0;
      digitalWrite(32, LOW);
    }
  }


//Battery Current - uses hass
  battCurrentDig = analogRead(11);
  battCurrentScaled = (float)battCurrent*Analog_Digital_Constant;
  battCurrentCalc = voltRefHass200*currNomHass200/(battCurrentScaled - battVoltConstant);

//Motor Current - uses hass
  motCurrentDig = analogRead(12);
  motCurrentScaled = (float)motCurrent*Analog_Digital_Constant;
  motCurrentCalc = voltRefHass200*currNomHass200/(motCurrentScaled - motVoltConstant);

//Auxilliary Current - uses has...boo!
  auxCurrentDig = analogRead(9);
  auxCurrentScaled = (float)auxCurrent*Analog_Digital_Constant;
  auxCurrentCalc = 12.5*auxCurrentScaled;

//Fuel Cell Current - uses has...boo!
  fcCurrentDig = analogRead(10);
  fcCurrentScaled = (float)fcCurrent*Analog_Digital_Constant;
  fcCurrentCalc = 12.5*fcCurrentScaled;

//Power Demand
  powerDemand = (auxCurrentCalc+motCurrent)*48;

  for (i = 0; i < 17; i++) {
    if (Power[i] > powerDemand) {
      pwmCurrent = Current[i];
      break;
    }
  }
  if (pwmCurrent > 50) {
    pwmVoltage = 255;
  }
  else {
    pwmVoltage = 51*pwmCurrent/10;
  }
  analogWrite(11, pwmVoltage);

//Calculate Current to be limited by boost converter
  sumOfCurrents = auxCurrentCalc+motCurrentCalc-battCurrentCalc;

//Send signal to the boost converter
  boostConverterCurrent_float = sumOfCurrents*Analog_Digital_Constant;
  boostConverterCurrent = floor(boostConverterCurrent_float);

//Timestamp
  timer = millis();
//Measure AmpHours consumed of battery
  if (timer - timer_prev > 200) { //Ignore ft longer than 0.2 second if it is will be insignificant
      ampHourBatt_temp = (float)battVoltageMeasured*battCurrentCalc;
      ampHourBatt_temp = ampHourBatt_temp/3600*.2;
      ampHourBatt = ampHourBatt + ampHourBatt_temp;
      EEPROM.write(EE_batt_amp_hour_addr, ampHourBatt);
      timer_prev = timer;
    }





//Serial.println("AmpHours Consumed:");
//Serial.println(ampHourBatt);



  printChoice = 6;
  if(digitalRead(6) == HIGH) { //button1
  printChoice = 1;
  printed = 0;
  }
  if(digitalRead(5) == HIGH) { //button2
  printChoice = 2;
  printed = 0;
  }
  if(digitalRead(8) == HIGH) { //button3
  printChoice = 3;
  printed = 0;
  }
  if(digitalRead(7) == HIGH) { //button4
  printChoice = 4;
  printed = 0;
  }
  if(digitalRead(9) == HIGH) { //button5
  printChoice = 5;
  if (buttonPushed == 0) {
    if (fanState < 2) {
      fanState = fanState + 1;
    }
    else {
      fanState = 0;
    }
  }
  else buttonPushed = 1;

  printed = 0;
  }
  else {
    buttonPushed = 0;
  }

  if (printed == 0) {
    lcd.clear();
    printed = 1;
    if (printChoice == 0){
      lcd.print("Hybrid Bike");
    }
    else if (printChoice == 1) {
      prev_printChoice = 1;
      lcd.print("Batt  Mot   Tank");
      //Serial.println(batt_avg_temp);
      lcd.setCursor(1, 2);
      lcd.print(batt_avg_temp);
      lcd.setCursor(7, 2);
      lcd.print(motortemp);
      lcd.setCursor(13, 2);
      lcd.print(tanktemp);
    }
    else if (printChoice == 2) {
      prev_printChoice = 2;
      lcd.print("iFC iAu iMt iBt");
      lcd.setCursor(1, 2);
      lcd.print(floor(fcCurrentCalc));
      lcd.setCursor(5, 2);
      lcd.print(floor(auxCurrentCalc));
      lcd.setCursor(9, 2);
      lcd.print(floor(motCurrentCalc));
      lcd.setCursor(13, 2);
      lcd.print(floor(battCurrentCalc));
      Serial.println(fcCurrentCalc);
      Serial.println(auxCurrentCalc);
      Serial.println(motCurrentCalc);
      Serial.println(battCurrentCalc);

    }
    else if (printChoice == 3) {
      prev_printChoice = 3;
      lcd.print("Battery SOC");
      lcd.setCursor(1, 2);
      lcd.print(battsoc);
    }
    else if (printChoice == 4) {
      prev_printChoice = 4;
      lcd.print("Amp Hour Used");
      lcd.setCursor(1, 2);
      lcd.print(ampHourBatt);
    }
    else if (printChoice == 5)
      prev_printChoice = 5;
      if (fanState == 0) {
        lcd.print("No Fans on");
        digitalWrite(34, LOW); //battery fan
        digitalWrite(32, LOW); //motor fan
      }
      if (fanState == 1) {
        lcd.print("Motor Fan on");
        digitalWrite(32, HIGH);
        digitalWrite(34, LOW);
      }
      if (fanState == 2) {
        lcd.print("Both fans on");
        digitalWrite(32, HIGH);
        digitalWrite(34, HIGH);
      }
      else{
      };
      printChoice = 6;
  }
  lcd_timer = millis();
  if (lcd_timer - lcd_timer_prev > 1000) {
    lcd_timer_prev = lcd_timer;
    printed = 0;
  }


//  }
  }
}
