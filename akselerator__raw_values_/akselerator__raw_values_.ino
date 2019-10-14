// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>

int *total;
int *gjennomsnitt;

int maks_maalinger = 50;
int sekv_nr = 0;
const int MPU_addr=0x68;  // I2C address of the MPU-6050
boolean akkurat_startet;

int *maalinger;

void setup(){
   maalinger = malloc(6* 50 * sizeof(int));
   for (int i = 0; i < 50; i++) {
      maalinger[i] = 0;
   }

   /*
   total = malloc(6 * sizeof(int));
   gjennomsnitt = malloc(2 * 6 * sizeof(int));
   for (int i = 0; i < 12; i++) {
      total[i] = 0;
      gjennomsnitt[i] = 0;
   }
   */

   Wire.begin();
   Wire.beginTransmission(MPU_addr);
   Wire.write(0x6B);  // PWR_MGMT_1 register
   Wire.write(0);     // set to zero (wakes up the MPU-6050)
   Wire.endTransmission(true);
   Serial.begin(9600);
}

void loop(){
   Wire.beginTransmission(MPU_addr);
   Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
   Wire.endTransmission(false);
   Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers

   maalinger[sekv_nr*6 + 0] = Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
   maalinger[sekv_nr*6 + 1] = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
   maalinger[sekv_nr*6 + 2] = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
   maalinger[sekv_nr*6 + 3] = Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
   maalinger[sekv_nr*6 + 4] = Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
   maalinger[sekv_nr*6 + 5] = Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

   /*
   total[0] += Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
   total[1] += Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
   total[2] += Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
   total[3] += Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
   total[4] += Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
   total[5] += Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    */

   sekv_nr++;

   if (sekv_nr >= maks_maalinger) {
      sort(maalinger, 50);
   }

   /*
   if (sekv_nr >= maks_maalinger) {
      for (int i = 0; i < 6; i++) {
        gjennomsnitt[i+6] = gjennomsnitt[i]; //flytter gammelt gjennomsnitt til slutt i arrayet
	     gjennomsnitt[i] = total[i] / maks_maalinger;   
       if (abs(gjennomsnitt[i] - gjennomsnitt[i+6]) > 25) {
          if (akkurat_startet) {
            akkurat_startet = false;
          } 
             Serial.print("JA, den beveger på seg!");
             print(gjennomsnitt);
          
       }
       total[i] = 0;   
      }
   }
   */
}

void sort(int *a, int size) {
   for (int l = 0; l < 6; i++) {

   }
    for (int i = 0; i < (size-1)*6; i+=6) {
        for (int o = 0; o < (size-(i+1)*6); o+=6) {
                if(a[o] > a[o+6]) {
                    int t = a[o];
                    a[o] = a[o+6];
                    a[o+6] = t;
                }
        }
    }
}

void print(int* verdier) {
   Serial.print("AcX = "); Serial.print(verdier[0]);
   Serial.print(" | AcY = "); Serial.print(verdier[1]);
   Serial.print(" | AcZ = "); Serial.print(verdier[2]);
   Serial.print(" | GyX = "); Serial.print(verdier[3]);
   Serial.print(" | GyY = "); Serial.print(verdier[4]);
   Serial.print(" | GyZ = "); Serial.println(verdier[5]);
}
