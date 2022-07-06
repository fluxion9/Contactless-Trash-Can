#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo;
SoftwareSerial serial(2, 3);

#define trig0 4
#define trig1 5
#define echo0 6
#define echo1 7
#define reset 8
#define redLED 12

#define SoS 0.0332 // cm/uS

bool full = false;

String Hannahs_Phone = "+2349074369133";
String Waste_Mgt = "";
float measuredDistance (trigPin, echoPin)
{
pinMode (trigPin, 1);
pinMode (echoPin, 0);

digitalWrite (trigPin, 0);
digitalWrite (trigPin, 1);
delayMicroseconds (10);
digitalWrite (trigPin, 0);

unsigned long duration = pulseIn (echoPin, 1);
duration /= 2;
float distance = SoS * duration;

return distance;
}

void sendSMS(String phoneNumber)
{
serial.print("AT+CMGF=1\r");
delay(100);
serial.print("AT+CMGS=\"" + phoneNumber + "\"");
delay(500);
serial.print("Trash Can is full at Hannah Orakwelu's Place, Please come and empty it. Thank you.");
delay(500);
serial.print((char)26);
delay(500);
serial.println();
delay(500);
}

void setup()
{
servo.attach(9);
serial.begin(9600)
pinMode (redLED, 1);
pinMode (reset, 2);
delay(15000);
serial.println("AT");
}

void loop()
{
if(!digitalRead(reset))
{
delay(1000);
full = false;
}

if (measuredDistance (trig0, echo0) < 5.0 && !full)
{
digitalWrite (redLED, 1);

int pos = servo.read();
if(pos > 10)
{
for(int i = pos; i >= 0; i--)
{
servo.write(i);
delay (20);
}
}
else{
servo.write(0);
}

full = true;

sendSMS(Hannahs_Phone);
delay(1000);
sendSMS(Waste_Mgt);
delay(1000);
}
else {
digitalWrite (redLED, 0);
full = false;
}

if(measuredDistance (trig1, echo1) < 30.0 && !full)
{
servo.write(90);
delay (5000);
int pos = servo.read();
if(pos > 10)
{
for(int i = pos; i >= 0; i--)
{
servo.write(i);
delay (20);
}
}
else{
servo.write(0);
delay(500);
}
}
}
