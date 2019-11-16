#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (7, 8); //

/* struct package */
/* { */
/*   int id=0; */
/*   boolean verdier[3]; */
/* }; */

/* typedef struct package Package; */
/* Package data; */

byte address = "0001";

boolean mottatt[3];

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, address);
  myRadio.startListening();
}


void loop()  
{

  if ( myRadio.available()) //ser etter data å motta
  {
    while (myRadio.available())
    {
      myRadio.read(mottatt, sizeof(boolean)*3 );
    }
    Serial.print("\nVerdier:");
    for (int i = 0; i < 3; i++) {
       Serial.print(mottatt[i] + ", ");
    }
    Serial.print("\n");
  }

}
