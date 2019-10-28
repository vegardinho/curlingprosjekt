int ATreshold_x = 1;
int ATreshold_y = 1;
int ATreshold_z = 1;

int GTreshold_x = 1;
int GTreshold_y = 1;
int GTreshold_z = 1;

boolean akselerometer(int x, int y, int z) {
   if (x < ATreshold_x && y < ATreshold_y && z < ATreshold_z) {
      return true;
   } else {
      return false;
   }
}

boolean gyrometer(int x, int y, int z) {
   if (x < GTreshold_x && y < GTreshold_y && z < GTreshold_z) {
      return true;
   } else {
      return false;
   }
}


boolean aks_gyro_thresh(int* maalinger) {
   if (gyrometer(maalinger[3], maalinger[4], maalinger[5]) && 
      akselerometer(maalinger[0], maalinger[1], maalinger[2])) {
      return true;
   } else {
      return false;
   }  
}
