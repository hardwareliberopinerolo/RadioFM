
//------Visualizza RSSI su serial monitor e LCD
void vis_rssi(void){
 
	radio.getRadioInfo(&info);
	int status_rssi=info.rssi;

  Serial.print(" - RSSI = ");
  Serial.print(status_rssi);
  Serial.println("dBuV");
  
  lcd.setCursor(8,1); //VERIFICARE POSIZIONE CURSORE
  lcd.print("RSSI: ");
  lcd.print(status_rssi);
  //lcd.print("dBuV");
}
//end--------------------------------

//------Visualizza la frequenza su serial monitor e LCD
void vis_frequenza(void){
	
  frequency = radio.getFrequency();   
  delay(100);
  
  Serial.print("Frequenza: ");
  Serial.print(frequency / 100);
  Serial.print(".");
  Serial.print(frequency % 100);
  Serial.print("MHz FM");

  lcd.clear();
  lcd.setCursor(0,0); //VERIFICARE POSIZIONE CURSORE
  lcd.print("Freq.: ");
  lcd.print(frequency / 100);
  lcd.print(".");
  lcd.print(frequency % 100);
  lcd.print("MHz FM");
}
//end--------------------------------


//---- Update the RDS ServiceName text on the LCD display
void DisplayServiceName(char *name)
{
  Serial.print("RDS:");
  Serial.println(name);
  
  lcd.setCursor(0,1); //VERIFICARE POSIZIONE CURSORE
  lcd.print("RDS: ");
  lcd.print(name);
} 
//end-----------------------------
