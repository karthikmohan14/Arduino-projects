int r=255,g=0,b=0;
int d=5;
int redPin=D5;
int greenPin=D6;
int bluePin=D7;
void setup() 
{
  Serial.begin(115200);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
}

void loop() 
{
Serial.println(analogRead(A0));
delay(100);
if(analogRead(A0)>500)
{
  for(int i=0;i<255;i++)
  {
    analogWrite(redPin,r);
    analogWrite(greenPin,g);
    analogWrite(bluePin,b);
    r-=1;
    g+=1;
    delay(d);
  }  
  for(int i=0;i<255;i++)
  {
    analogWrite(redPin,r);
    analogWrite(greenPin,g);
    analogWrite(bluePin,b);
    g-=1;
    b+=1;
    delay(d);
   }  
  for(int i=0;i<255;i++)
  {
    analogWrite(redPin,r);
    analogWrite(greenPin,g);
    analogWrite(bluePin,b);
    b-=1;
    r+=1;
    delay(d);
  }
}else{
    //print r if false
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,LOW);
    }
}
