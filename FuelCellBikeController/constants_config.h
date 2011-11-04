// voltage sensor calibration
#define V_BAT_C           84       // [mV/step]
#define V_FC_C            85       // [mV/step]

// current sensor calibration
// C [amps / step] = 5 [volts] / 1023 [steps] * Ir [rated milliAmps] / 0.625 [volts / Ir amps] / amplifier_gain
#define I_FC_C            55.86    // 5/1023*50e3/0.625/7.0 [mA/step]
#define I_BAT_LOW_C      391       // 5/1023*50e3/0.625/1   [mA/step]
#define I_BAT_HIGH_C    1564       // 5/1023*200e3/0.625/1  [mA/step]
#define I_MOTOR_C       1564       // 5/1023*200e3/0.625/1  [mA/step]

// pressure sensor calibration
#define P_TANK_C          20.8067  // 6.894*617.5*5/1023 [kPa]

// SOC config
#define SOC_CAPACITY       5.000e3 // [mAh]

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
// Interval
#define SOC_CC_INTERVAL    1e4       // [us]
// Current to capacity conversion
// 1/360 [uAh/mA] = 1e3 [uA/mA] * 1/3600 [h/s] * 1e-6 [s/us] * 1e4 [us]
#define SOC_CC_I_TO_CAP_C  1/360
// Efficiency
#define SOC_CC_CHARGE_EFF  0.9
#define SOC_CC_DISCHA_EFF  0.9

// current controller proportional constant
#define I_CONTROLLER_P  5e-3       // [steps/amp]

// Iteration time
#define ITER_INTERVAL    100       // [ms]

// Daq config
#define DAQ_CSV_SEPARATOR ";"

// Menu config
#define MENU_PAGE_COUNT    9
#define MENU_REFR_TIME   300       // [ms]

// Button config
#define BUTTON_DEAD_TIME 300       // [ms]
