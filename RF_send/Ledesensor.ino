#include <CapacitiveSensor.h>     //legger til bibliotek 

CapacitiveSensor cap = CapacitiveSensor(4,2);     //sender pin setter til 4, receive pin settes til 2
boolean kapasitansSensor = 0;                   //Setter opp en True/False verdi
const int threshold = 300;                      //setter et Threshold

long* kap_maalinger;                          //def variabel

void setup_kapasitiv() {                  
  Serial.begin(9600);                   //setter data-raten i bits per sekund 
  delay(100);                           //trenger ikke målinger så ofte; setter derfor på delay - for bedre ytelse på resten
  myRadio.begin();                      //begynner transitering [bib inkludert (RF24.h) i RF_send]
  myRadio.setChannel(115); //kanal vi vil kommunisere med mottakeren
  myRadio.setPALevel(RF24_PA_MAX); //bruker mer strøm, men gir lengt mulig rekkevidde [Power amplifier]
  myRadio.setDataRate( RF24_250KBPS ) ; //lavest mulig dataoverføring for lengre rekkevidde
  myRadio.openWritingPipe( addresses[0]);     //setter destinasjon for hvor vi tenker å skrive
  myRadio.stopListening();                    //stopper forrige punkt

  kap_maalinger = malloc(sizeof(long) * maks_maalinger);      //sizeof - returnerer antall bytes, malloc - reserverer minne av spesifisert mengde
}

void kap_maaling(){
  kap_maalinger[sekv_nr] = cap.capacitiveSensor(30);      //lager en liste med verdier som du får inn med kapasitetsmålinger med en nøyaktighet på 30 bytes
}

long kap_median() {
   qsort(kap_maalinger, maks_maalinger, sizeof(long), int_compare);   //qsort(liste, antall elem, størrelse, funksjon som sammenligner to elem) [funk int_compare def i "RF_send"] 
   return kap_maalinger[maks_maalinger/2];    //returnerer medianen
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
