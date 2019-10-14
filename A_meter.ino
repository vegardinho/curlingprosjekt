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


boolean akselerometer_og_gyrometer() {
  if (Gyrometer(int x, int y, int z) == true && akselerometer(int x, int y, int z)) == true) {
    return true;
  } else {
    return false;
  }  
  }
