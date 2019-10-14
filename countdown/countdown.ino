/*
  Created by Bruno Calou Alves, May, 2015.
  Link - https://github.com/brunocalou/Timer
  Read LICENSE for more information.
*/
#include <CapacitiveSensor.h>
CapacitiveSensor cap = CapacitiveSensor(4, 2);
boolean kapasitansSensor = 0;
const int threshold = 300;
#include "timer.h"

//Timer object
Timer timer;

int counter = 60;

void countdown() {
  Serial.println(counter);
  if (counter > 0) {
    counter -= 1;
  }
}

void kapSensor() {
  long sensorVerdi = cap.capacitiveSensor(30);

  if (sensorVerdi < threshold) {
    timer.setCallback(countdown);
  } else {
    timer.pause();
  }

}
void setup()
{
  Serial.begin(9600);

  //Set the interval in milliseconds
  //and the number of repetitions
  timer.setInterval(1000, 6);

  //Set our callback function
  timer.setCallback(countdown);
  //Start the timer
  timer.start();
}

void loop()
{
  timer.update();
  kapSensor();
  //Update the timer
}
