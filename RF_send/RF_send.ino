#include <SPI.h>
#include "RF24.h"		//bib for kommunisere mellom enheter

RF24 myRadio (7, 8);		//pin 7 er 
byte addresses[][6] = {"0"}; //må være lik på mottaker

int maks_maalinger = 10;
int sekv_nr = 0;
int* med_denne;
int* med_forrige;
int ant_var = 6;
long* send_array;
long* gammel_send_array;
boolean* ja_nei;

void setup() {
   med_denne = malloc((ant_var) * sizeof(int));
   med_forrige = malloc((ant_var) * sizeof(int));
   send_array = malloc((ant_var + 1) * sizeof(long));
   gammel_send_array = malloc((ant_var + 1) * sizeof(long));
   ja_nei = malloc((ant_var + 1) * sizeof(boolean));

   setup_kapasitiv();
   setup_gyro_aks();
}

void loop() {
   kap_maaling();
   gyro_maaling();

   sekv_nr++;

   if (sekv_nr >= maks_maalinger) {
      for (int i = 0; i < ant_var; i++) {
	 gammel_send_array[i] = send_array[i];
      }

      send_array = (long*) gyro_median();
      send_array[ant_var] = kap_median();

      if (aks_thresh(send_array, gammel_send_array)) {
	 ja_nei[0] = true;
      } else {
	 ja_nei[0] = false;
      }
      if (gyro_thresh(send_array, gammel_send_array)) {
	 ja_nei[1] = true;
      } else {
	 ja_nei[1] = false;
      }
      if (kap_thresh(send_array, gammel_send_array)) {
	 ja_nei[2] = true;
      } else {
	 ja_nei[2] = false;
      }

      if (ja_nei[0] || ja_nei[1] || ja_nei[2]) {
	 send(ja_nei, sizeof(boolean), 3);
      }

      /* print(send_array); */
      print_ja_nei();

      sekv_nr = 0;
   }
}

void send(void* verdier, int str, int ant) {
   myRadio.write(&verdier, str*ant);
}

int int_compare(const void *a, const void *b) {
   int* tall_a = (int*) a;
   int* tall_b = (int*) b;
   return *tall_a - *tall_b;
}

void print_ja_nei() {
   Serial.print("Aks = "); Serial.print(ja_nei[0]);
   Serial.print("Gyro = "); Serial.print(ja_nei[1]);
   Serial.print("Kap = "); Serial.print(ja_nei[2]);
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
