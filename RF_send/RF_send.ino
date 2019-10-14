#include <CapacitiveSensor.h>
CapacitiveSensor cap = CapacitiveSensor(4,2);
boolean kapasitansSensor = 0;
const int threshold = 300;
#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"}; //må være lik på mottaker


void setup()
{
  Serial.begin(9600);
  delay(100);
  myRadio.begin();  
  myRadio.setChannel(115); //kanal vi vil kommunisere med mottakeren
  myRadio.setPALevel(RF24_PA_MAX); //bruker mer strøm, men gir lengt mulig rekkevidde
  myRadio.setDataRate( RF24_250KBPS ) ; //lavest mulig dataoverføring for lengre rekkevidde
  myRadio.openWritingPipe( addresses[0]);
  myRadio.stopListening();
  delay(1000);
}

void loop(){
  kapSensor();

}

void kapSensor(){
  long sensorVerdi = cap.capacitiveSensor(30); 
  
  if (sensorVerdi > threshold){
    Serial.println("Sensor på");
    const char text[32] = "Sensor på";
    myRadio.write(&text, sizeof(text));
  }else{
    Serial.println("Sensor av");
    const char text[32] = "Sensor av";
    myRadio.write(&text, sizeof(text));
  }

  delay(1000); //sender data hvert sekund
}
