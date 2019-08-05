
//-----------Setup-------------------------------------
void setup(){
  Serial.begin(9600);
//-----------------------------
  delay(100);
  Serial.println(programma); //scrive sulla il nome dello sketch

//Configura LCD
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
//-----------------------------
  delay(100);
  
// Initialize the Radio 
  radio.init();
// Enable information to the Serial port
  radio.debugEnable();
//  radio.debugRegisters();
// Configurazione Volume 
  radio.setMono(false);
  radio.setMute(false);
  radio.setVolume(8);
  delay(100);

//---Legge frequenza dalla eeprom
	Legge_eeprom_frequenza();

//Initialize the radio to the West-FM band. The mode will set the proper receiver bandwidth
// configura la frequenza di accensione
  radio.setBandFrequency(RADIO_BAND_FM, numero_int);
  delay (100);
  vis_frequenza();
  vis_rssi();

// setup the information chain for RDS data.
  radio.attachReceiveRDS(RDS_process);
  rds.attachServicenNameCallback(DisplayServiceName);

//---Configura conteggi per pulsanti
  t_prec_PU1=millis();
  //t_prec_PU2=millis();

} //end--------------Setup-----------------------------------------
