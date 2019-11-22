#include <CapacitiveSensor.h>     //legger til bibliotek 
#include <SPI.h>		//bib for kommunisere mellom enheter
#include "RF24.h"		//

#define SERIAL_RATE 9600
#define RADIO_RATE 9600

//sender pin setter til 4, receive pin settes til 2
CapacitiveSensor cap = CapacitiveSensor(4,2); 
RF24 myRadio (9, 10);	//setter CSN og CE pins. Vil være send og receive pin til SPI busen 
const byte address[6] = "00001"; //må være lik på mottaker

const int KAP_SAMPLES = 1;
const int MAKS_MAALINGER = 10;		//def variabler og pekere
const int ANT_VAR = 6;
int sekv_nr = 0;

long* med_denne;
long* send_array;
long* kap_maalinger;                         
long* gammel_send_array;
boolean* ja_nei;

boolean old_aks_mvmt = false;		//def boolean
boolean new_aks_mvmt = false;
boolean old_gyro_mvmt = false;
boolean new_gyro_mvmt = false;
boolean old_kap_mvmt = false;
boolean new_kap_mvmt = false;

boolean send_pakke = false;

/* Alokkerer minne til variabler, og kaller på setup-funksjonene for gyro/aks og kap */
 /* sizeof - returnerer antall bytes, malloc - reserverer minne av spesifisert mengde */
void setup() {
   med_denne = malloc((ANT_VAR) * sizeof(long));
   send_array = malloc((ANT_VAR + 1) * sizeof(long));
   gammel_send_array = malloc((ANT_VAR + 1) * sizeof(long));
   ja_nei = malloc((ANT_VAR + 1) * sizeof(boolean));
   kap_maalinger = malloc(sizeof(long) * MAKS_MAALINGER);      
	
   cap.reset_CS_AutoCal(); // Set capacitive sensor to auto calibrate
   setup_gyro_aks();		//def i RF_send
   setup_radio();		//def i gyro_aks

   Serial.begin(SERIAL_RATE);                   //setter data-raten i bits per sekund 
}

void setup_radio() {                  
  myRadio.begin();                      //begynner transitering [bib inkludert (RF24.h) i RF_send]
  myRadio.setChannel(115); //kanal vi vil kommunisere med mottakeren
  myRadio.setPALevel(RF24_PA_MAX); //bruker mer strøm, men gir lengt mulig rekkevidde [Power amplifier]
  myRadio.setDataRate(RF24_250KBPS) ; //lavest mulig dataoverføring for lengre rekkevidde
  myRadio.openWritingPipe(address);     //setter destinasjon for hvor vi tenker å skrive
  myRadio.stopListening();                    //stopper forrige punkt

/* Samler en maaling fra kap.-senor og gyro, kaller på median-funksjon, threshold-funksjon og
 * sjekker om verdier skal sendes */
void loop() {
   kap_maalinger[sekv_nr] = cap.capacitiveSensor(KAP_SAMPLES);      
   gyro_maaling();

   sekv_nr++;

   if (sekv_nr >= MAKS_MAALINGER) {
      for (int i = 0; i < ANT_VAR + 1; i++) {
	 gammel_send_array[i] = send_array[i];
      }

      send_array = gyro_median();
      send_array[ANT_VAR] = kap_median();

      new_aks_mvmt = aks_thresh(send_array, gammel_send_array);
      if (new_aks_mvmt && !old_aks_mvmt) {
	 ja_nei[0] = true;
	 send_pakke= true;
      } else if (!new_aks_mvmt && old_aks_mvmt) {
	 ja_nei[0] = false;
	 send_pakke= true;
      }

      new_gyro_mvmt = gyro_thresh(send_array, gammel_send_array);
      if (new_gyro_mvmt && !old_gyro_mvmt) {
	 ja_nei[1] = true;
	 send_pakke= true;
      } else if (!new_gyro_mvmt && old_gyro_mvmt) {
	 ja_nei[1] = false;
	 send_pakke= true;
      }

      new_kap_mvmt = kap_thresh(send_array); 
      if (new_kap_mvmt) {
	 ja_nei[2] = true;
      } else {
	 ja_nei[2] = false;
      }

      if (new_kap_mvmt != old_kap_mvmt) {
	 send_pakke = true;
      }


      if (send_pakke) {
	 send(ja_nei, sizeof(boolean), 3);
	 print_ja_nei();
	 /* send(send_array, sizeof(int), 7); */
      }

      old_kap_mvmt = new_kap_mvmt;
      old_gyro_mvmt = new_gyro_mvmt;
      old_aks_mvmt = new_aks_mvmt;
      send_pakke= false;   

      print(send_array);
      sekv_nr = 0;
   }
}

void send(void* verdier, int str, int ant) {
   myRadio.write(verdier, str*ant);
}


void kap_maaling(){
   kap_maalinger[sekv_nr] = cap.capacitiveSensor(1);      
}

long kap_median() {
   bubble_sort_long(kap_maalinger, MAKS_MAALINGER);
   return kap_maalinger[MAKS_MAALINGER/2];    //returnerer medianen
}

// Sorteringsalgoritme for long-verdier.
void bubble_sort_long(long a[], int size) {
   for(int i=0; i<(size-1); i++) {
      for(int o=0; o<(size-(i+1)); o++) {
	 if(a[o] > a[o+1]) {
	    int t = a[o];
	    a[o] = a[o+1];
	    a[o+1] = t;
	 }
      }
   }
}

void print_ja_nei() {
   Serial.print("Aks = "); Serial.print(ja_nei[0]);
   Serial.print(" Gyro = "); Serial.print(ja_nei[1]);
   Serial.print(" Kap = "); Serial.print(ja_nei[2]);
   Serial.print("\n");
}

void print(long* verdier) {
   Serial.print("AcX = "); Serial.print(verdier[0]);
   Serial.print(" | AcY = "); Serial.print(verdier[1]);
   Serial.print(" | AcZ = "); Serial.print(verdier[2]);
   Serial.print(" | GyX = "); Serial.print(verdier[3]);
   Serial.print(" | GyY = "); Serial.print(verdier[4]);
   Serial.print(" | GyZ = "); Serial.print(verdier[5]);
   Serial.print(" | Kap = "); Serial.println(verdier[6]);
}
