
//----Gestione Seriale---------------------------------------------
void Gestione_Seriale(void){
    if(Serial.available()>0){
    ricez_car=Serial.read();
    delay(10);
    if(in_ric==0){in_ric=1;} //In ricezione.
    conta=0;
    ricez_array[ricez_ind++]=ricez_car;  //Ricezione frequenza dalla Seriale.
  }
  if(in_ric){
    if(conta>5000){  //Fine ricezione frequeza dalla Seriale.
      in_ric=0;
      numero=atoi(ricez_array);     //Converte in intero.
		Salva_eeprom_frequenza(); //Memorizza la frequenza sulla eeprom
      radio.setFrequency(numero);   //Imposta la frequenza.
      delay(200);
      vis_frequenza();   //Visualizza frequenza.
      vis_rssi();        //     "     RSSI.

      
      
      Serial.println("----------------------------------------------------------");
      svuota_array();    //Preparazione per prossima ricezione dalla Seriale.
      ricez_car=' ';     //      "       "      "        "       "      "
      ricez_ind=0;       //      "       "      "        "       "      "
    }  
    conta++;
  } 

} //end----Gestione Seriale---------------------------------------------
  

