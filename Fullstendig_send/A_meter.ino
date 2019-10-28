int ATreshold_x = ;
int ATreshold_y = ;
int ATreshold_z = ;

int GTreshold_x = ;
int GTreshold_y = ;
int GTreshold_z = ;

boolean akselerometer(int x, int y, int z) {
   if (x < ATreshold_x && y < ATreshold_y && z < ATreshold_z) {
      return true;
   } else {
      return false;
   }
}

boolean Gyrometer(int x, int y, int z) {
   if (x < GTreshold_x && y < GTreshold_y && z < GTreshold_z) {
      return true;
   } else {
      return false;
   }
}


boolean aks_gyro_thresh(int* maalinger) {
   if (Gyrometer(int maalinger[3], int maalinger[4], int maalinger[5]) == true && 
      akselerometer(int maalinger[0], int maalinger[1], int maalinger[2])) == true) {
      return true;
   } else {
      return false;
   }  
}
