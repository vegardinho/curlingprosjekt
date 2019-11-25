#include <Wire.h>
#include <stdlib.h>

#define MPU6050_PWR_MGMT_1 0x6B
#define GYRO_ADDR 0x1B
#define AKS_ADDR 0x1C
#define GYRO_AKS_FULL_SCALE 0x10
#define WAKE_MODE 0

long *maalinger;		//def peker
const int MPU6050_I2C_ADDRESS = 0x68;

void setup_gyro_aks(){
   //Allokerer minne
   maalinger = malloc(ANT_VAR * MAKS_MAALINGER * sizeof(long));

   Wire.begin(); // Initialize the 'Wire' class for the I2C-bus. 
   // Start queuing bytes to be transferred to device with specified address
   Wire.beginTransmission(MPU6050_I2C_ADDRESS); 
   Wire.write(MPU6050_PWR_MGMT_1);  // Choose PWR_MGMT_1 register
   Wire.write(WAKE_MODE);	    // Wake up device (1=sleep)
   Wire.endTransmission();	    // Transmits queued bytes by "write" and ends transmission

   Wire.beginTransmission(MPU6050_I2C_ADDRESS);
   Wire.write(GYRO_ADDR);	    // Talk to the GYRO_CONFIG register 
   Wire.write(GYRO_AKS_FULL_SCALE); // Set to 1000deg/s full scale
   Wire.endTransmission();

   Wire.beginTransmission(MPU6050_I2C_ADDRESS);
   Wire.write(AKS_ADDR);	    //Talk to the ACCEL_CONFIG register 
   Wire.write(GYRO_AKS_FULL_SCALE); // Set to +/- 8g full scale range
   Wire.endTransmission();
}


/*får inn verdiene fra gyro og aks. lager en liste med første de 10 første verdiene for x-akse akelerometer osv*/ 
   // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
   // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L) */
   // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) */
   //Hoppe over temp
   // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) */
   // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) */
   // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) */
void gyro_maaling(){  
   Wire.beginTransmission(MPU6050_I2C_ADDRESS);
   Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
   Wire.endTransmission(false);
   Wire.requestFrom(MPU6050_I2C_ADDRESS,14,true);  // request a total of 14 registers

   maalinger[MAKS_MAALINGER*0 + sekv_nr] = Wire.read()<<8|Wire.read();  
   maalinger[MAKS_MAALINGER*1 + sekv_nr] = Wire.read()<<8|Wire.read();  
   maalinger[MAKS_MAALINGER*2 + sekv_nr] = Wire.read()<<8|Wire.read();  
   Wire.read()<<8|Wire.read();
   maalinger[MAKS_MAALINGER*3 + sekv_nr] = Wire.read()<<8|Wire.read();  
   maalinger[MAKS_MAALINGER*4 + sekv_nr] = Wire.read()<<8|Wire.read();  
   maalinger[MAKS_MAALINGER*5 + sekv_nr] = Wire.read()<<8|Wire.read();  
}

/* Sorterer listen "maalinger" 10 for 10 (elementer) for så å regne ut medianen i de 10 */
/* sorterte elementene */
long* gyro_median() {

   for (int i = 0; i < MAKS_MAALINGER; i++) {
      bubble_sort_long(maalinger + i*MAKS_MAALINGER, MAKS_MAALINGER);
      med_denne[i] = maalinger[i*MAKS_MAALINGER + MAKS_MAALINGER/2];
   }

   return med_denne;
}
