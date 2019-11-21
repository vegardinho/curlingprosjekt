#include <CapacitiveSensor.h>     //legger til bibliotek 

CapacitiveSensor cap = CapacitiveSensor(4,2);     //sender pin setter til 4, receive pin settes til 2
boolean kapasitansSensor = 0;                   //Setter opp en True/False verdi
const int threshold = 300;                      //setter et Threshold


void kap_maaling(){
  kap_maalinger[sekv_nr] = cap.capacitiveSensor(30);      //lager en liste med verdier som du får inn med kapasitetsmålinger med en nøyaktighet på 30 bytes
}

long kap_median() {
   bubble_sort_long(kap_maalinger, maks_maalinger);
   return kap_maalinger[maks_maalinger/2];    //returnerer medianen
}

