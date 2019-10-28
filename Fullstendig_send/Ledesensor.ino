#include <CapacitiveSensor.h>
CapacitiveSensor cap = CapacitiveSensor(4,2);
boolean kapasitansSensor = 0;
const int threshold = 300;

int* kap_maalinger;

void setup_kapasitiv() {
  Serial.begin(9600);
  delay(100);
  myRadio.begin();  
  myRadio.setChannel(115); //kanal vi vil kommunisere med mottakeren
  myRadio.setPALevel(RF24_PA_MAX); //bruker mer strøm, men gir lengt mulig rekkevidde
  myRadio.setDataRate( RF24_250KBPS ) ; //lavest mulig dataoverføring for lengre rekkevidde
  myRadio.openWritingPipe( addresses[0]);
  myRadio.stopListening();

  kap_maalinger = malloc(sizeof(int) * maks_maalinger);
}

void kap_maaling(){
  kap_maalinger[sekv_nr] = cap.capacitiveSensor(30);
}

int kap_median() {
   qsort(kap_maalinger, maks_maalinger, sizeof(int), int_compare);
   return kap_maalinger[maks_maalinger/2];
}

  

  /*
  
  if (sensorVerdi > threshold){
    Serial.println("Sensor på");
    const char text[32] = "Sensor på";
    myRadio.write(&text, sizeof(text));
  }else{
    Serial.println("Sensor av");
    const char text[32] = "Sensor av";
    myRadio.write(&text, sizeof(text));
  }
}
*/
