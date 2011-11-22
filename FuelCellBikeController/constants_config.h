// Loop iteration time
#define ITER_INTERVAL    100       // [ms]

// Daq config
#define DAQ_CSV_SEPARATOR ";"

// LCD config
#define LCD_COLS          16
#define LCD_ROWS           2

// Button config
#define BUTTON_DEAD_TIME 300       // [ms]

#define BUTTON_NEXT        1
#define BUTTON_PREVIOUS    2
#define BUTTON_ACTION      3
#define BUTTON_UNUSED_1    4
#define BUTTON_UNUSED_2    5

// Menu config
#define MENU_REFR_TIME   300       // [ms]
#define PAGE_DAQ           1
#define PAGE_VELOCITY      2
#define PAGE_SOC           3
#define PAGE_FC_CTRL       4
#define PAGE_CURRENT       5
#define PAGE_VOLTAGE       6
#define PAGE_POWER         7
#define PAGE_TEMP          8
#define PAGE_HYDROGEN      9
#define PAGE_STATS        10
#define MENU_PAGE_COUNT   10

// Fan control config
#define FAN_BAT_T_THRES   30       //  [deg C]
#define FAN_MOT_T_THRES   30       //  [deg C]


// voltage sensor calibration
#define V_BAT_C           87.59       // [mV/step]
#define V_FC_C            87.59       // [mV/step]
#define V_BAT_ZERO       142
#define V_FC_ZERO        179

// current sensor calibration
// C [amps / step] = 5 [volts] / 1023 [steps] * Ir [rated milliAmps] / 0.625 [volts / Ir amps] / amplifier_gain
#define I_FC_C            55.86    // 5/1023*50e3/0.625/7.0 [mA/step]
#define I_BAT_LOW_C      391       // 5/1023*50e3/0.625/1   [mA/step]
#define I_BAT_HIGH_C    1564       // 5/1023*200e3/0.625/1  [mA/step]
#define I_MOTOR_C       1564       // 5/1023*200e3/0.625/1  [mA/step]

#define I_FC_ZERO        191
#define I_BAT_LOW_ZERO   509
#define I_BAT_HIGH_ZERO  509
#define I_MOTOR_ZERO     509

#define I_BAT_CROSSOVER  200e3

// Pressure sensor calibration
#define P_TANK_C          20.8067  // 6.894*617.5*5/1023 [kPa]

// Hydrogen mass estimation
#define M_HYDROGEN_C     242.47    // 10^3 [Pa/kPa] * V_tanks [m^3] * M_h2 [g/mol] / R [J/mol K] = 1000*1*2.016/8.3145=242.47

// General SOC config
#define SOC_CAPACITY       25e3    // [mAh]

// SOC by OCV estimation
// Fitted data measured at a 2A load to account for the 12v system still drawing power
// SOC_OCV = SOC_OCV_C0 + SOC_OCV_C1*(v_bat-SOC_V_OFFSET)^1 + ... + SOC_OCV_Cn*(v_bat-SOC_V_OFFSET)^n
#define SOC_OCV_V_MIN      4.322e4 // [mV]
#define SOC_OCV_V_MAX      5.019e4 // [mV]
#define SOC_OCV_V_OFFSET   4.605e4 // [mV]
#define SOC_OCV_V_SCALE    1.767e3
#define SOC_OCV_C5         4.546e4
#define SOC_OCV_C4        -1.396e5
#define SOC_OCV_C3        -7.084e4
#define SOC_OCV_C2         5.947e5
#define SOC_OCV_C1        -1.356e6
#define SOC_OCV_C0         1.821e6

// SOC by coulomb counting
#define SOC_CC_INTERVAL    1e4     // [us]
#define SOC_CC_CHARGE_EFF  0.85
#define SOC_CC_DISCHA_EFF  0.85
#define SOC_CC_I_TO_CAP_C  1/360   // 1/360 [uAh/mA] = 1e3 [uA/mA] * 1/3600 [h/s] * 1e-6 [s/us] * 1e4 [us]

// Current controller
#define I_CONTROLLER_C     5.1e-3  // [steps/mA]
#define I_CONTROLLER_FB_ON true    // feedback on?
#define I_CONTROLLER_FB_C  2.0e-3  // [steps/mA]

// Velocity
#define VELOCITY_C       220       // 1760 [mm wheel circumference] / 8 [pulses] = 220 [mm/pulse]
