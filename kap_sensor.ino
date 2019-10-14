#include <CapacitiveSensor.h>
CapacitiveSensor cap = CapacitiveSensor(4,2);
boolean kapasitansSensor = 0;
const int threshold = 300;

void kapSensor(){
  long sensorVerdi = cap.capacitiveSensor(30); 
  
  if (sensorVerdi > threshold){
    Serial.println("Sensor på");
    const char text[32] = "Sensor av";
    myRadio.write(&text, sizeof(text));
  }else{
    Serial.println("Sensor av");
    const char text[32] = "Sensor på";
    myRadio.write(&text, sizeof(text));
  }

  delay(1000); //sender data hvert sekund
}
