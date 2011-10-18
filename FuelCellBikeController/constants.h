// arduino pinout

// digital/pwm top row
#define I_CONTROL       5
#define T_TANK          6
#define T_MOTOR         7
#define FAN_MOTOR      10

// digital double row left
#define FAN_BAT        38
#define SOL_CONTACT    40
#define SOL_MOTOR      42

// digital double row right
#define LCD_D4         23
#define LCD_D5         25
#define LCD_D6         27
#define LCD_D7         29
#define LCD_EN         31
#define LCD_RS         33
#define BUTTON_1       35
#define BUTTON_2       37
#define BUTTON_3       39
#define BUTTON_4       41
#define BUTTON_5       43

#define LED_WARNING    49
#define T_BAT          51
#define SW_KICKSTAND   53

// analog in
#define V_FC           A0
#define V_BAT          A1
#define P_TANK         A2
#define POT            A3

#define I_MOTOR        A8
#define I_BAT_HIGH     A9
#define I_BAT_LOW      A10
#define I_FC           A11

// voltage sensor calibration
#define V_BAT_C         0.0840 // [volts/step]
#define V_FC_C          0.0850 // [volts/step]

// current sensor calibration
// calculation C [amps / step] = 5 [volts] / 1023 [steps] * Ir [rated Amps] / 0.625 [volts / Ir amps] / amplifier_gain
#define I_FC_C          0.05586 // 5/1023*50/0.625/7.0 [amps/step]
#define I_BAT_LOW_C     0.3910  // 5/1023*50/0.625/1   [amps/step]
#define I_BAT_HIGH_C    1.5640  // 5/1023*200/0.625/1  [amps/step]
#define I_MOTOR_C       1.5640  // 5/1023*200/0.625/1  [amps/step]

// SOC estimation using open circuit voltage
// SOC = SOC_OCV_C0 + SOC_OCV_C1*(v_bat-SOC_V_OFFSET)^1 + SOC_OCV_C1*(v_bat-SOC_V_OFFSET)^2 + ... + SOC_OCV_C7*(v_bat-SOC_V_OFFSET)^7
#define SOC_OCV_CAP   5000
#define SOC_OCV_OFFSET  23.15
#define SOC_OCV_C7      -9.759
#define SOC_OCV_C6      25.94
#define SOC_OCV_C5      77.05
#define SOC_OCV_C4    -253.8
#define SOC_OCV_C3     -60.65
#define SOC_OCV_C2     702.2
#define SOC_OCV_C1   -1453
#define SOC_OCV_C0    1899

#define I_CONTROL_C      0.1953  // [amps/step]
#define I_CONTROLLER_P   5       // [steps/amp]
