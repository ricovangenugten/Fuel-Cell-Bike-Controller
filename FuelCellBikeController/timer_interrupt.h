void timer_interrupt() {

  if (daq_on()) {
    unsigned long timestamp = daq_measurement_start();
    unsigned long id = daq_measurement_id();

    // header
    if (id == 0) {
      sd_bw.putStr("time,id,meas1,meas2\r\n");
      sd_bw.writeBuf();
    }

    // write measurement
    sd_bw.putNum(timestamp);
    sd_bw.putStr(",");
    sd_bw.putNum(id);
    sd_bw.putStr(",1,2\r\n");
    sd_bw.writeBuf();

  daq_measurement_end();
  }

}
