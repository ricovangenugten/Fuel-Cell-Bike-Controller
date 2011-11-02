// file system object
SdFat sd_fs;

// file object
SdFile sd_file;

// buffered file writer
BufferedWriter sd_bw;

bool sd_new_file() {
  if (!sd_fs.init(SPI_FULL_SPEED)) {
    lcd_message("SD: Init failed");
    return 0;
  }

  char name[] = "DATA000.CSV";

  for (uint8_t i = 0; i < 1000; i++) {
    name[4] = i/100 + '0';
    name[5] = i%100/10 + '0';
    name[6] = i%10 + '0';
    if (sd_fs.exists(name)) continue;
    sd_file.open(name,  O_WRITE | O_CREAT | O_EXCL);
    sd_bw.init(&sd_file);
    break;
  }
  if (!sd_file.isOpen()) {
    lcd_message("SD: Open error");
    return 0;
  }
  else {
    lcd_message(name);
  }
  return 1;
}

bool sd_close_file() {
  sd_bw.writeBuf();
  return sd_file.close();
}

