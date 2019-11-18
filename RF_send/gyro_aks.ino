// Standardlib required for qsort()
#include <Wire.h>
#include <stdlib.h>

int *maalinger;

const int MPU_addr=0x68;  // I2C address of the MPU-6050
boolean akkurat_startet;

void setup_gyro_aks(){
  
   //Allokerer minne
   maalinger = malloc(ant_var * maks_maalinger * sizeof(int));

   //Nullstiller verdier
   for (int i = 0; i < maks_maalinger; i++) {
      maalinger[i] = 0;
      if (i % 5 == 0) {
	      med_denne[i / 5] = 0;
	      med_forrige[i / 5] = 0;
      }
   }

   Wire.begin();
   Wire.beginTransmission(MPU_addr);
   Wire.write(0x6B);  // PWR_MGMT_1 register
   Wire.write(0);     // set to zero (wakes up the MPU-6050)
   Wire.endTransmission(true);
   Serial.begin(9600);

   Wire.beginTransmission(0b1101000);
   Wire.write(0x1B); //gyroscope config
   Wire.write(0x00000000);
   Wire.endTransmission();

   Wire.beginTransmission(0b1101000);
   Wire.write(0x1C); //akselerometer config
   Wire.write(0b00011000);
   Wire.endTransmission();
}

void process_gyro_data(int* gyro_arr) {
  gyro_arr[0] = gyro_arr[0] / 131.0;
  gyro_arr[1] = gyro_arr[1] / 131.0;
  gyro_arr[2] = gyro_arr[2] / 131.0;
}

void process_accel_data(int* acc_arr) {
  acc_arr[0] = acc_arr[0] / 16.3840;
  acc_arr[1] = acc_arr[1] / 16.3840;
  acc_arr[2] = acc_arr[2] / 16.3840;
}

/* Lagrer verdi, og sender medianverdien dersom verdien er nummer 50 i rekken */
void gyro_maaling(){  
   Wire.beginTransmission(MPU_addr);
   Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
   Wire.endTransmission(false);
   Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers

   // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
   maalinger[maks_maalinger*0 + sekv_nr] = Wire.read()<<8|Wire.read();  
   // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L) */
   maalinger[maks_maalinger*1 + sekv_nr] = Wire.read()<<8|Wire.read();  
   // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) */
   maalinger[maks_maalinger*2 + sekv_nr] = Wire.read()<<8|Wire.read();  
   // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) */
   //Hoppe over temp
   Wire.read()<<8|Wire.read();
   maalinger[maks_maalinger*3 + sekv_nr] = Wire.read()<<8|Wire.read();  
   // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) */
   maalinger[maks_maalinger*4 + sekv_nr] = Wire.read()<<8|Wire.read();  
   // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) */
   maalinger[maks_maalinger*5 + sekv_nr] = Wire.read()<<8|Wire.read();  
}

int* gyro_median() {
   for (int i = 0; i < ant_var; i++) {
      qsort(maalinger + i*maks_maalinger, maks_maalinger, sizeof(int), int_compare);
      med_forrige[i] = med_denne[i];
      med_denne[i] = maalinger[i*maks_maalinger + maks_maalinger/2];
   }

   return med_denne;
}

void reset_aks_gyro() {
   for (int i = 0; i < maks_maalinger * ant_var; i++) {
      maalinger[i] = 0;
   }
}
