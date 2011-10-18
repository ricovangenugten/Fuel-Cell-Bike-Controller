float ocv_capacity(float v_bat) {

  int params[8] = {SOC_OCV_C0, SOC_OCV_C1, SOC_OCV_C2, SOC_OCV_C3, SOC_OCV_C4, SOC_OCV_C5, SOC_OCV_C6, SOC_OCV_C7};
  float soc_ocv = 0;
  float current_term = 0;

  for(int i=0;i<8;i++) {
    current_term = params[i];
    for(int j=0;j<i;j++) {
        current_term = current_term*(v_bat/2-SOC_OCV_OFFSET);
    }
    soc_ocv += current_term;
  }

  if (soc_ocv > SOC_OCV_CAP) soc_ocv = SOC_OCV_CAP;
  if (soc_ocv < 0) soc_ocv = 0;

  return soc_ocv;
}

float ocv_capacity_to_soc(float cap) {
  return 100-cap/(SOC_OCV_CAP/100);
}
