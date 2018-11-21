#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

double roll = 0.00, pitch = 0.00, x = 0.00, y = 0.00, z = 0.00;
double mini = 0.00, maxi = 0.00, xf = 0.00, yf = 0.00, zf = 0.00, xd = 0.00, yd = 0.00, zd = 0.00;
int timecounter = 0;

void setup() {
 Serial.begin(115200);
 if (!accel.begin()) {
  Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
  while (1);
 }
 accel.setRange(ADXL345_RANGE_16_G);
}

void checkMovement() {
 if (xd > yd && xd > zd && xd > mini) {
  Serial.print("x rules");
  Serial.print(",");
 }
 if (yd > xd && yd > zd && yd > mini) {
  Serial.print("y rules");
  Serial.print(",");
 }
 if (zd > yd && zd > xd && zd > mini) {
  Serial.print("z rules");
  Serial.print(",");
 }
}


void checkFits(){
  if ((timecounter % 250) == 0) {
   xd = xf - x;
   yd = yf - y;
   zd = zf - z;
   Serial.print("F");
   Serial.print(",");
   checkMovement();
  }
}

void cascadeMovement() {
  timecounter++;
  Serial.print(timecounter);
  Serial.print(",");
  if (timecounter > 10000) {
   timecounter = 0;
  } else if ((timecounter % 250) == 0) {
   xd = xf - x;
   yd = yf - y;
   zd = zf - z;
   x = xf;
   y = yf;
   z = zf;
   Serial.print("!");
   Serial.print(",");
   checkMovement();
  }
}  
  void moveAccelerometer() {
   sensors_event_t event;
   accel.getEvent( & event);
   xf = (event.acceleration.x) / 9.8;
   Serial.print(xf);
   Serial.print(",");
   yf = (event.acceleration.y) / 9.8;
   Serial.print(yf);
   Serial.print(",");
   zf = (event.acceleration.z) / 9.8;
   Serial.print(zf);
   Serial.println("");
   delay(10);
  }
void loop() {
 cascadeMovement();
 moveAccelerometer();
}
