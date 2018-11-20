void setup() {
  Serial.begin(115200);
}

void loop() {
if(digitalRead(D6)==LOW){
  Serial.println("Obstacle");
}
else{
  Serial.println("Clear");
}
delay(100);
}
