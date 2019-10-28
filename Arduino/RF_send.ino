#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"}; //må være lik på mottaker

int maks_maalinger = 10;
int sekv_nr = 0;
int* med_denne;
int* med_forrige;
int ant_var = 6;
long* send_array;

void setup() {
   med_denne = malloc((ant_var) * sizeof(int));
   med_forrige = malloc((ant_var) * sizeof(int));
   send_array = malloc((ant_var + 1) * sizeof(long));

  setup_kapasitiv();
  setup_gyro_aks();
}

void loop() {
   kap_maaling();
   gyro_maaling();

   sekv_nr++;

   if (sekv_nr >= maks_maalinger) {
      send_array = (long*) gyro_median();
      send_array[ant_var] = kap_median();
      
      send(send_array);
      print(send_array);
      
      sekv_nr = 0;
   }
}

void send(long* verdier) {
   myRadio.write(&verdier, sizeof(int)*(ant_var + 1));
}

int int_compare(const void *a, const void *b) {
   int* tall_a = (int*) a;
   int* tall_b = (int*) b;
   return *tall_a - *tall_b;
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