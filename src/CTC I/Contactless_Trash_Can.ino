#include <Servo.h>
Servo myservo;
#define trigPin 3
#define echoPin 4
#define buzzer 12
float speedOfSound = 0.0332, setDistance = 30.0;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  myservo.attach(9);
}

void loop() {
  myservo.write(0);
  delay(100);
  if(measuredDistance() <= setDistance)
  {
    beep();
    while(measuredDistance() <= setDistance)
    {
      myservo.write(90);
      delay(100);
    }
    delay(2000);
    myservo.write(0);
  }
}

float measuredDistance()
{
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  unsigned long echo = pulseIn(echoPin, HIGH);
  echo /= 2;
  float distance = echo * speedOfSound;
  return distance;
}

void beep()
{
  digitalWrite(buzzer, HIGH);
  delay(400);
  digitalWrite(buzzer, LOW);
}
//9f@TM
