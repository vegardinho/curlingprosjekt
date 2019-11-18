#include <SPI.h>		//bib for kommunisere mellom enheter
#include "RF24.h"		//

RF24 myRadio (9, 10);		//setter CSN og CE pins. Vil være send og receive pin til SPI busen 
const byte address[6] = "00001"; //må være lik på mottaker

int maks_maalinger = 10;		//def variabler og pekere
int sekv_nr = 0;
long* med_denne;
int ant_var = 6;
long* send_array;
long* gammel_send_array;
boolean* ja_nei;
long* kap_maalinger;                         

boolean old_aks_mvmt = false;		//def boolean
boolean new_aks_mvmt = false;
boolean old_gyro_mvmt = false;
boolean new_gyro_mvmt = false;
boolean old_kap_mvmt = false;
boolean new_kap_mvmt = false;

boolean send_pakke = false;

void setup() {
   med_denne = malloc((ant_var) * sizeof(long));
   send_array = malloc((ant_var + 1) * sizeof(long));
   gammel_send_array = malloc((ant_var + 1) * sizeof(long));
   ja_nei = malloc((ant_var + 1) * sizeof(boolean));

   kap_maalinger = malloc(sizeof(long) * maks_maalinger);      
 //sizeof - returnerer antall bytes, malloc - reserverer minne av spesifisert mengde */
	
   setup_radio();
   setup_gyro_aks();
}

void setup_radio() {                  
  Serial.begin(9600);                   //setter data-raten i bits per sekund 
  /* delay(100);                           //trenger ikke målinger så ofte; setter derfor på delay - for bedre ytelse på resten */
  myRadio.begin();                      //begynner transitering [bib inkludert (RF24.h) i RF_send]
  myRadio.setChannel(115); //kanal vi vil kommunisere med mottakeren
  myRadio.setPALevel(RF24_PA_MAX); //bruker mer strøm, men gir lengt mulig rekkevidde [Power amplifier]
  myRadio.setDataRate( RF24_250KBPS ) ; //lavest mulig dataoverføring for lengre rekkevidde
  myRadio.openWritingPipe(address);     //setter destinasjon for hvor vi tenker å skrive
  myRadio.stopListening();                    //stopper forrige punkt
}



/* Samler en maaling fra kap.-senor og gyro, kaller på median-funksjon, threshold-funksjon og
 * sjekker om verdier skal sendes */
void loop() {
   kap_maaling();
   gyro_maaling();

   sekv_nr++;

   if (sekv_nr >= maks_maalinger) {
      for (int i = 0; i < ant_var + 1; i++) {
	 gammel_send_array[i] = send_array[i];
      }

      send_array = (long*) gyro_median();
      send_array[ant_var] = kap_median();

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

      new_kap_mvmt = kap_thresh(send_array, gammel_send_array); 
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

      /* print(send_array); */
      sekv_nr = 0;
   }
}

void send(void* verdier, int str, int ant) {
   myRadio.write(verdier, str*ant);
}

int int_compare(const void *a, const void *b) {
   int* tall_a = (int*) a;
   int* tall_b = (int*) b;
   return *tall_a - *tall_b;
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
