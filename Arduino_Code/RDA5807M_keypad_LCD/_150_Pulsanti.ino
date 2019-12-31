//-------Gestione Pulsanti Analogici-------------------------
void Gestione_Pulsanti_Analogici(){
   val_A0=analogRead(0); //lettura valore input analogico A0
   
   if(val_A0<1000){
   Serial.print("Valore Pulsante: ");
   Serial.println(val_A0);
   }

   if(val_A0>=0 && val_A0<50){//Se il valore letto rientra nel range di valori...
		if(millis()-t_prec_PU1>t_PU1){//antirimbalzo pulsante
		  radio.seekUp();  //Ricerca auto avanti.
		  delay (300);
		  vis_frequenza();
		  vis_rssi();
		  t_prec_PU1=millis();
		}  
	}

	if(val_A0>=400 && val_A0<520){ //409
		if(millis()-t_prec_PU1>t_PU1){
		  radio.seekDown();  //Ricerca auto indietro.
		  
		  delay (300);
		  vis_frequenza();
		  vis_rssi();
		  t_prec_PU1=millis();
		}  
	}

//-------SCANSIONE MANUALE DELLA FREQUENZA-------
	if(val_A0>50 && val_A0<150){ //101
		if(millis()-t_prec_PU1>t_PU1){
			freq_scan = radio.getFrequency();    
			freq_scan=freq_scan+10;//modifica
			radio.setFrequency(freq_scan);
			delay(50);
			vis_frequenza();
			vis_rssi();
			t_prec_PU1=millis();
		}  
	}

	if(val_A0>200 && val_A0<300){ //258
		if(millis()-t_prec_PU1>t_PU1){
			freq_scan = radio.getFrequency();    
			freq_scan=freq_scan-10;//modifica
			radio.setFrequency(freq_scan);
			delay(50);
			vis_frequenza();
			vis_rssi();
		  t_prec_PU1=millis();
		}  
	  }
}
//end-------Gestione Pulsanti Analogici-------------------------
