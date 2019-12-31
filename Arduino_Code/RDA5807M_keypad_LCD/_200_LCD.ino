
//------Visualizza RSSI su serial monitor e LCD
void vis_rssi(void){
 
	radio.getRadioInfo(&info);
	int status_rssi=info.rssi;

  Serial.print(" - RSSI = ");
  Serial.print(status_rssi);
  Serial.println("dBuV");
  
  lcd.setCursor(12,0); //VERIFICARE POSIZIONE CURSORE
  lcd.print("R:");
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
  lcd.print("F:");
  lcd.print(frequency / 100);
  lcd.print(".");
  lcd.print(frequency % 100);
  lcd.print("MHz");
}
//end--------------------------------


//---- Update the RDS ServiceName text on the LCD display
void DisplayServiceName(char *name)
{
radio_name=name;
Serial.print("RDS:");
Serial.print(name);
Serial.print(" - ");
Serial.println(radio_name);

} 
//end-----------------------------



//---- Update the RDS ServiceName text on the LCD display
void vis_radio(void)
{
  Serial.print("RDS:");
  Serial.println(radio_name);
  
  lcd.setCursor(0,1); //VERIFICARE POSIZIONE CURSORE
  lcd.print("RDS: ");
  lcd.print(radio_name);
} 
//end-----------------------------
