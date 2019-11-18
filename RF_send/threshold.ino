long kap_threshold;

long endring_x;
long endring_y;
long endring_z;

long kap_verdi;
long kap_gammel;
long kap_endring;

long x;
long y;
long z;

long x_old;
long y_old;
long z_old;

const long AKS_SENS = 80;
const long GYRO_SENS = 100;

boolean aks_thresh(long* send_array, long* gammel_send_array) {
      x = send_array[0];
   y = send_array[1];
   z = send_array[2];

   x = abs(x);
   y = abs(y);
   z = abs(z);

   x_old = gammel_send_array[0];
   y_old = gammel_send_array[1];
   z_old = gammel_send_array[2];

   x_old = abs(x_old);
   y_old = abs(y_old);
   z_old = abs(z_old);

   long a_thresh_x = AKS_SENS;
   long a_thresh_y = AKS_SENS;
   long a_thresh_z = AKS_SENS;

   endring_x = send_array[0] - gammel_send_array[0];
   endring_x = abs(endring_x);
   endring_y = send_array[1] - gammel_send_array[1];
   endring_y = abs(endring_y);
   endring_z = send_array[2] - gammel_send_array[2];

   endring_z = abs(endring_z);

   if (endring_x > a_thresh_x || endring_y > a_thresh_y || endring_z > a_thresh_z) {
      return true;
   }
   return false;
}

boolean gyro_thresh(long* send_array, long* gammel_send_array) {
   x = send_array[3];
   y = send_array[4];
   z = send_array[5];

   x = abs(x);
   y = abs(y);
   z = abs(z);

   x_old = gammel_send_array[3];
   y_old = gammel_send_array[4];
   z_old = gammel_send_array[5];

   x_old = abs(x_old);
   y_old = abs(y_old);
   z_old = abs(z_old);

   long g_thresh_x = GYRO_SENS;
   long g_thresh_y = GYRO_SENS;
   long g_thresh_z = GYRO_SENS;

   endring_x = send_array[3] - gammel_send_array[3];
   endring_x = abs(endring_x);
   endring_y = send_array[4] - gammel_send_array[4];
   endring_y = abs(endring_y);
   endring_z = send_array[5] - gammel_send_array[5];

   endring_z = abs(endring_z);

   if (endring_x > g_thresh_x || endring_y > g_thresh_y || endring_z > g_thresh_z) {
      return true;
   }
   return false;
}

boolean kap_thresh(long* send_array, long* gammel_send_array) {
   kap_threshold = 200;

   kap_verdi = send_array[6];
   kap_verdi = abs(kap_verdi);
   /*  */
   /* kap_gammel = gammel_send_array[6]; */
   /* kap_gammel = abs(kap_gammel); */
   /*  */
   /* kap_endring = kap_verdi - kap_gammel; */
   /* kap_endring = abs(kap_endring); */

   if (kap_verdi > kap_threshold) {
      return true;
   }
   return false;
}

void print_ting() {
   Serial.print("x = "); Serial.print(x_old); 
   Serial.print("x = "); Serial.print(x);
   Serial.print("x = "); Serial.println(endring_x);
   Serial.println();

   Serial.print("y = "); Serial.print(y_old); 
   Serial.print("y = "); Serial.print(y);
   Serial.print("x = "); Serial.println(endring_y);
   Serial.println();

   Serial.print("z = "); Serial.print(z_old); 
   Serial.print("z = "); Serial.print(z);
   Serial.print("x = "); Serial.println(endring_z);
   Serial.println();
}
