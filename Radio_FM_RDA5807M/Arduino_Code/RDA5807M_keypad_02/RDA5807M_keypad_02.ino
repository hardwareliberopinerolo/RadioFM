#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#include <radio.h>
#include <RDA5807M.h>
#include <RDSParser.h>


char programma[]="RDA5807M_keypad_02"; //Nome Sketch
char ricez_array[10];
char ricez_car;
byte ricez_ind=0;
byte in_ric=0;
int conta=0;
unsigned int numero=0;
byte PU1=11;
byte PU2=12;
int EE_alto=0;
int EE_basso=0;
int pass=0;
int num=0;
int numero_int=0;
//int status;
int frequency;
int freq_scan;//modifica
int freq_scan1;//modifica
int freq_status;//modifica
int val_A0;//variabile per lettura pulsanti
unsigned long t_prec_freq=0;//variabile per tempi lunghissimi non va in overflow (49giorni)
const int t_PU1=100;//tempo antirimbalzo pulsante
unsigned long t_prec_PU1;
/*
const int t_PU2=100;
unsigned long t_prec_PU2; //tempo antirimbalzo pulsante
*/
const int Tempo_salvataggio_eeprom=5000;

//Inizializzazioni Oggetti 
LiquidCrystal lcd(8,9,4,5,6,7);

RDA5807M radio;    // Create an instance of a RDA5807 chip radio
RDSParser rds; //Create an instance of RDS parser

RADIO_INFO info;

