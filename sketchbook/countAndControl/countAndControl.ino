#include <Servo.h>

Servo speedController;

const int FORWARD = 0;
const int REVERSE = 1;

int potPin    = A0;
int sensorPin = A1;
int ledPin    = 13;
int state     = 0;
int counter   = 0;
int threshold = 30;
int direction = FORWARD;

int potVal;
int sensorVal;

void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  speedController.attach(9);
  Serial.begin(9600);
}

unsigned int getDirection(int val)
{
  if(val > 89)
    return FORWARD;
  else
    return REVERSE;
}

void count(){
  if(direction == FORWARD)
    counter++;
  else
    counter--;
}

int getCounter(int val)
{
  if (val > threshold && state==0){
    state = 1;
    count();
  }
  else if(val < threshold && state==1){
    state = 0;
    count();
  }
}

void loop()
{
  sensorVal = analogRead(sensorPin);
  potVal    = analogRead(potPin);
  potVal    = map(potVal, 0, 1023, 0, 179);
  direction = getDirection(potVal);
  speedController.write(potVal);
  Serial.println(getCounter(sensorVal));
  digitalWrite(ledPin, state);
}
