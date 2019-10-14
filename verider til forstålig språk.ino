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
