//-------Loop------------------------------------------------------
void loop(){
	//Gestione_Seriale();

  tempo=millis()-t_prec_vis;
  //Serial.print("tempo: ");
  //Serial.println(tempo);
    if(tempo > Tempo_vis){
        Serial.println("Aggiorno LCD");
   vis_frequenza();
   vis_rssi();
   vis_radio();
   //DisplayServiceName(char *name)
   t_prec_vis=millis();
  }
  Gestione_Pulsanti_Analogici();
	Salva_ultima_stazione();


// check for RDS data
	radio.checkRDS();
}
//end-----------------------------
