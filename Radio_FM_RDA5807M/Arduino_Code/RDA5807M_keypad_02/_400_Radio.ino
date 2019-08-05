//------Salva ultima stazione sulla eprom-----------------------
void Salva_ultima_stazione(void){
	if(millis()-t_prec_freq>Tempo_salvataggio_eeprom){
		freq_status = radio.getFrequency();
		if (freq_status!=numero_int){
			Salva_eeprom_frequenza();
			t_prec_freq=millis();//aggiorno la variabile t_prec_freq con il valore attuale di millis
		}
	}
}
//end-----------------------------



//---- Processa dati RDS
void RDS_process(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4) {
  rds.processData(block1, block2, block3, block4);
}
//end-----------------------------
