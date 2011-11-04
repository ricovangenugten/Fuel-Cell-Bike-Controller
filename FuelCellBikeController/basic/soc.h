uint32_t soc_cc, soc_init = 0;

uint32_t soc_by_ocv(uint32_t v_bat) {

  float params[6] = {SOC_OCV_C0, SOC_OCV_C1, SOC_OCV_C2, SOC_OCV_C3, SOC_OCV_C4, SOC_OCV_C5};
  float soc_ocv = 0;
  float current_term = 0;

  if (v_bat < SOC_OCV_V_MIN) v_bat = SOC_OCV_V_MIN;
  if (v_bat > SOC_OCV_V_MAX) v_bat = SOC_OCV_V_MAX;

  for(int i=0;i<6;i++) {
    current_term = params[i];
    for(int j=0;j<i;j++) {
      current_term = current_term*((v_bat-SOC_OCV_V_OFFSET)/SOC_OCV_V_SCALE);
    }
    soc_ocv += current_term;
  }

  return roundf(soc_ocv);
}

void soc_by_cc_count() {
  float i_bat = i_battery();

  if (i_bat < 0) {
      // charging
      soc_cc += roundf(i_bat*SOC_CC_I_TO_CAP_C*SOC_CC_CHARGE_EFF);
  } else {
      // discharging
      soc_cc += roundf(i_bat*SOC_CC_I_TO_CAP_C/SOC_CC_DISCHA_EFF);
  }
}

void soc_by_cc_start(uint32_t init) {
  soc_cc = init;
  soc_init = init;
  Timer1.initialize(SOC_CC_INTERVAL);
  Timer1.attachInterrupt(soc_by_cc_count);
}

void soc_by_cc_stop() {
  Timer1.detachInterrupt();
}

uint32_t soc_by_cc() {
  return soc_cc/1e3;
}

uint32_t soc_init_val() {
  return soc_init/1e3;
}

int soc_percentage(uint32_t charge) {
  return 100-charge*100/SOC_CAPACITY;
}
