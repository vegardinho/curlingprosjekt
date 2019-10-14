Wire.beginTransmission(0b1101000)
Wire.write(0x1B); //gyroscope config
Wire.write(0x00000000)
Wire.endTransmission()

Wire.beginTransmission(0b1101000)
Wire.write(0x1C); //akselerometer config
Wire.write(0b00011000)
Wire.endTransmission()

void ProcessGyroData() {
  rotX = gyroX / 131.0
  rotY = gyroY / 131.0
  rotZ = gyroZ / 131.0
}

void ProcessAccelData() {
  gForceX = accelX / 16384.0
  gForceY = accelY / 16384.0
  gForceY = accelZ / 16384.0
}
   Wire.beginTransmission(0b1101000);
   Wire.write(0x1B); //gyroscope config
   Wire.write(0x00000000);
   Wire.endTransmission();

   Wire.beginTransmission(0b1101000);
   Wire.write(0x1C); //akselerometer config
   Wire.write(0b00011000);
   Wire.endTransmission();

   /*
   if (sekv_nr >= maks_maalinger) {
      for (int i = 0; i < ant_var; i++) {
        gjennomsnitt[i+ant_var] = gjennomsnitt[i]; //flytter gammelt gjennomsnitt til slutt i arrayet
	     gjennomsnitt[i] = total[i] / maks_maalinger;   
       if (abs(gjennomsnitt[i] - gjennomsnitt[i+ant_var]) > 25) {
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

/*  */
/* void sort(int *a, int size) { */
/*    for (int l = 0; l < ant_var; l++) { */
/*  */
/*    } */
/*     for (int i = 0; i < (size-1)*ant_var; i+=ant_var) { */
/*         for (int o = 0; o < (size-(i+1)*ant_var); o+=ant_var) { */
/*                 if(a[o] > a[o+ant_var]) { */
/*                     int t = a[o]; */
/*                     a[o] = a[o+ant_var]; */
/*                     a[o+ant_var] = t; */
/*                 } */
/*         } */
/*     } */
/* } */
/*  */
   /*
   total[0] += Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
   total[1] += Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
   total[2] += Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
   total[3] += Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
   total[4] += Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
   total[5] += Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    */

   /* maalinger[0] = 2; */
   /* maalinger[1] = 3; */
   /* maalinger[2] = 4; */
   /* maalinger[3] = 1; */
   /*  */
   /* Serial.print(*(maalinger + 1)); */
   /* delay(10000000); */
   /*  */
   /* qsort(maalinger, 4, sizeof(int), int_compare); */
   /*  */
   /* Serial.print("Nå kommer det"); */
   /* Serial.print(maalinger[0]); */
   /* Serial.print(maalinger[1]); */
   /* Serial.print(maalinger[2]); */
   /* Serial.print(maalinger[3]); */
   /* delay(1000000); */
}


   /*
      total = malloc(ant_var * sizeof(int));
      gjennomsnitt = malloc(2 * ant_var * sizeof(int));
      for (int i = 0; i < 12; i++) {
      total[i] = 0;
      gjennomsnitt[i] = 0;
      }
    */
