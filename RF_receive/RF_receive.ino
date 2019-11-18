#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (9, 10); //

byte address[6] = "00001";
boolean mottatt[3];

void setup() 
{
   Serial.begin(9600);
   myRadio.begin(); 
   myRadio.setChannel(115); 
   myRadio.setPALevel(RF24_PA_MAX);
   myRadio.setDataRate(RF24_250KBPS) ; 
   myRadio.openReadingPipe(0, address);
}


void loop()  
{
   myRadio.startListening();
   if ( myRadio.available()) //ser etter data å motta
   {
      while (!myRadio.available());
      myRadio.read(&mottatt, sizeof(mottatt));

      for (int i = 0; i < 3; i++) {
	 if (mottatt[i] == true) {
	    Serial.write(1);
	 } else {
	    Serial.write(0);
	 }
	 mottatt[i] = false;
      }

      myRadio.stopListening();
   }
}
