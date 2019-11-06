int a_thresh_x = 
int a_thresh_y = abs(send_array[1] - gammel_send_array[1]);
int a_thresh_z = abs(send_array[2] - gammel_send_array[2]);

int g_thresh_x = abs(send_array[3] - gammel_send_array[3]);
int g_thresh_y = abs(send_array[4] - gammel_send_array[4]);
int g_thresh_z = abs(send_array[5] - gammel_send_array[5]);

int kap_threshold = abs(send_array[6] - gammel_send_array[6]);


boolean aks_thresh(long* send_array, long* gammel_send_array) {
   endring_x = abs(send_array[0] - gammel_send_array[0]);
   endring_y = abs(send_array[1] - gammel_send_array[1]);
   endring_z = abs(send_array[2] - gammel_send_array[2]);

   if (endring_x > a_thresh_x || endring_y > a_thresh_y || endring_z > a_thresh_z) {
      return true;
   }
   return false;
}

boolean gyro_thresh(long* send_array, long* gammel_send_array) {
   endring_x = abs(send_array[0] - gammel_send_array[0]);
   endring_y = abs(send_array[1] - gammel_send_array[1]);
   endring_z = abs(send_array[2] - gammel_send_array[2]);

   if (endring_x > g_thresh_x || endring_y > g_thresh_y || endring_z > g_thresh_z) {
      return true;
   }
   return false;
}

boolean kap_thresh(long* send_array, long* gammel_send_array) {
   if (verdi > kap_threshold) {
      return true;
   }
   return false;
}
