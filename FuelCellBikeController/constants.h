// arduino pinout

#define BUTTON_1        5
#define BUTTON_2        6
#define BUTTON_3        7
#define BUTTON_4        8
#define BUTTON_5        9
#define FAN_MOTOR      32
#define FAN_BAT        34
#define SOL_CONTACT    36
#define T_MOTOR        38
#define SW_KICKSTAND   39
#define SOL_MOTOR      40
#define T_TANK         42
#define T_BAT          45
#define LCD_D4         46
#define LCD_D5         47
#define LCD_D6         48
#define LCD_D7         49
#define LCD_EN         51
#define LCD_RS         53
#define BC_I_LIMIT     11
#define I_BAT_LOW      A9
#define I_BAT_HIGH    A10
#define I_FC          A11
#define I_MOTOR       A12
#define P_TANK        A13
#define V_FC          A14
#define V_BAT         A15

//other
#define V_BAT_C         0.0840
#define V_FC_C          0.0850

// current sensor calibration
// calculation C = 5 [volts] / 1023 [steps] * Ir [rated Amps] / 0.625 [volts / Ir amps] / amplifier_gain
#define I_FC_C          0.05586 // = 5/1023*50/0.625/7.0
#define I_BAT_LOW_C     0.3910  // = 5/1023*50/0.625/1
#define I_BAT_HIGH_C    0.7174  // = 5/1023*200/0.625/2.18
#define I_MOTOR_C       0.7174  // = 5/1023*200/0.625/2.18
