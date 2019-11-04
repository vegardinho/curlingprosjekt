int ATreshold_x = 1;
int ATreshold_y = 1;
int ATreshold_z = 1;

int GTreshold_x = 1;
int GTreshold_y = 1;
int GTreshold_z = 1;

int kap_threshold = 1;

boolean aks_thresh(int x, int y, int z) {
   if (x < ATreshold_x || y < ATreshold_y || z < ATreshold_z) {
      return true;
   }
   return false;
}

boolean gyro_thresh(int x, int y, int z) {
   if (x < GTreshold_x || y < GTreshold_y || z < GTreshold_z) {
      return true;
   }
   return false;
}

boolean kap_thresh(int verdi) {
   if (verdi > kap_threshold) {
      return true;
   }
   return false;
}
