#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

double roll = 0.00, pitch = 0.00, x = 0.00, y = 0.00, z = 0.00;
double mini = 0.00, fmini = 0.10, maxi = 0.00, xf = 0.00, yf = 0.00, zf = 0.00, xd = 0.00, yd = 0.00, zd = 0.00;
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

int i = 0;
int flag[5] = {0,0,0,0,0};
void checkFits()
{
  Serial.print("checking for seizures : ");
  Serial.print(flag[0]);Serial.print(",");
  Serial.print(flag[1]);Serial.print(",");
  Serial.print(flag[2]);Serial.print(",");
  Serial.print(flag[3]);Serial.print(",");
  Serial.print(flag[4]);Serial.print("");
  i++;
  if(i==5){i=0;}
  if ((timecounter % 1) == 0) {
   xd = xf - x;
   yd = yf - y;
   zd = zf - z;
   if(xd < 0){xd *= -1;}
   if(yd < 0){yd *= -1;}
   if(zd < 0){zd *= -1;}
  if(xd >  fmini && yd >  fmini && zd >  fmini){
    flag[i] = 1;
    }else{
      flag[i] = 0;
      }
  if(flag[0] == 1 && flag[1] == 1 && flag[2] == 1 && flag[3] == 1 && flag[4] == 1){
  Serial.print("you have seizures !!");  
  }  
}
}
void loop() {
  timecounter++;
  Serial.print(timecounter);
  Serial.print(",");
  if (timecounter > 1250) {
     timecounter = 0;
  }
  else if (timecounter > 1000){
    checkFits();
  }
  else if ((timecounter % 50) == 0) {
   xd = xf - x;
   yd = yf - y;
   zd = zf - z;
   x = xf;
   y = yf;
   z = zf;
   Serial.print("!");
   Serial.print(",");
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
sensors_event_t event;
   accel.getEvent( & event);
   xf = (event.acceleration.x) / 9.8;
   Serial.print(xd);
   Serial.print(",");
   yf = (event.acceleration.y) / 9.8;
   Serial.print(yd);
   Serial.print(",");
   zf = (event.acceleration.z) / 9.8;
   Serial.print(zd);
   Serial.println("");
   delay(10);
}
