float time;
float time_prev = 0;
float ts;
float Ibatt = 50;
float SOC = 0.5;

#define ADDITIONAL_SETUP_PRESENT
void additional_setup() {
  lcd.clear();
  lcd.print("SOC testing");
  delay(1000);

}

void loop(){

	if (time_prev == 0)
	{
		time_prev = millis();
	}

	if (SOC < 0)
	{
	Ibatt = -50;
	}
	else if (SOC > 1)
	{
	Ibatt = 50;
	}


  time = millis();
  ts = (time - time_prev)/1000;
  time_prev = time;

  SOC = SOC - Ibatt*ts/18000;

  lcd.clear();
  lcd.print("SOC: ");

  //prints time since program started
  lcd.print(SOC*100);
  lcd.print(" %");
  // wait a second so as not to send massive amounts of data
  delay(500);
}
