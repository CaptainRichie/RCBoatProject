#include <Servo.h>
#include <String.h>

int servoPin = 6;
int throttlePin = 3;

String message;
String angle;
String throttle;

double ang;
double thr;

Servo Rudder;

void setup() {
  Rudder.attach(servoPin);
  Rudder.write(90);
  pinMode(throttlePin,OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(5);
}

void loop() {
  if(Serial.available() > 0)
  {
    // Bluetooth message reception:
    message = Serial.readString();
    if(message.length() >= 5)
    {
      // Rudder command:
      angle = message.substring(0,3);//This method has been tested and approved.
      //Serial.println(angle); // Debugging code.
      ang = angle.toInt();
      if(ang > 0)
      {
        Rudder.write(ang);
      }
      else
      {
        Rudder.write(0);
      }

      // Throttle command:
      throttle = message.substring(3,5);
      //Serial.println(throttle); // Debugging code.
      thr = throttle.toInt();
      analogWrite(throttlePin,((thr/99)*255));
    }
  }
}

    
