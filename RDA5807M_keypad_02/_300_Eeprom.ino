//---Legge frequenza dalla eeprom
void Legge_eeprom_frequenza(void){
  EE_alto=EEPROM.read(10);
  delay(30);
  EE_basso=EEPROM.read(11);
  delay(30);
  numero_int=EE_alto*256+EE_basso;
    delay (30);
}
//end--------------------------------

//---Scrive frequenza dalla eeprom
void Salva_eeprom_frequenza(void){
      EE_alto=numero/256;
      EEPROM.write(10,EE_alto);
      delay(30);
      EE_basso=numero-EE_alto*256;
      EEPROM.write(11,EE_basso);
      delay(30);
}
//end--------------------------------
