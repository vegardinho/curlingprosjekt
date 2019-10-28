#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"}; //må være lik på mottaker

int maks_maalinger = 50;
int sekv_nr = 0;
int* med_denne;
int* med_forrige;
int ant_var = 6;

void setup() {
   med_denne = malloc((ant_var+1) * sizeof(int));
   med_forrige = malloc((ant_var+1) * sizeof(int));

  setup_kapasitiv();
  setup_gyro_aks();
}

void loop() {
   //kap_maaling();
   gyro_maaling();

   sekv_nr++;

   if (sekv_nr >= maks_maalinger) {
      gyro_median();
      //med_denne[ant_var+1] = kap_median();

      send(med_denne);
      print(med_denne);
      sekv_nr = 0;
   }
}

void send(int* verdier) {
   myRadio.write(&verdier, sizeof(int)*(ant_var + 1));
   Serial.print("SENDT!\n");
}

int int_compare(const void *a, const void *b) {
   int* tall_a = (int*) a;
   int* tall_b = (int*) b;
   return *tall_a - *tall_b;
}

void print(int* verdier) {
      Serial.print("AcX = "); Serial.print(verdier[0]);
      Serial.print(" | AcY = "); Serial.print(verdier[1]);
      Serial.print(" | AcZ = "); Serial.print(verdier[2]);
      Serial.print(" | GyX = "); Serial.print(verdier[3]);
      Serial.print(" | GyY = "); Serial.print(verdier[4]);
      Serial.print(" | GyZ = "); Serial.println(verdier[5]);
  }
