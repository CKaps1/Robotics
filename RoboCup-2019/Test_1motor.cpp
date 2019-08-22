/*
	This code is a test of a single motor using the class from "servo.cpp"
	It reads numbers from the serial port and sets the speed to that number.
	Direction is based on the sign.
	Min is -255 (full speed reverse) max is 255 (full speed forward)
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define _print Serial.println

class motor
{
  #define _d _direction
  #define _F FORWARD
  #define _S RELEASE // stopped or stationary
  #define _B BACKWARD
  #define myMotor _m
  public:
  Adafruit_MotorShield* AFMS;
  Adafruit_DCMotor *_m;
  int _direction = _S;

  public:
    short _speed;
    motor(short port)
    {
      _speed=0;
      AFMS = new Adafruit_MotorShield();
      myMotor = AFMS->getMotor(port);
      AFMS->begin();
      Serial.begin(9600);
      Serial.println("Constructor worked");
    }
    ~motor()
    {
      delete AFMS;
    }
    public: void set(int __speed) // direction = sign
    {
      _speed = (short)__speed;
      if (_speed > 0)
      {
        switch (_d)
        {
          case _F:
              myMotor->setSpeed(255);
              delay(50);
              _m->setSpeed(abs(_speed));
              _print(_speed);
          break;
          case _S:
              _d = _F;
              myMotor->run(_d);
              myMotor->setSpeed(255);
              delay(50);
              _m->setSpeed(abs(_speed));
              _d = _F;
              _print(_speed);
          break;

          case _B:
              myMotor->run(_S);
              delay(25);
              _d = _F;
              myMotor->run(_d);
              myMotor->setSpeed(255);
              delay(25);
              _m->setSpeed(abs(_speed));
              _print(_speed);
          break;
        }
      }
      else
            if (_speed < 0)
      {

        switch (_d)
        {
          case _B:
              myMotor->setSpeed(255);
              delay(50);
              _m->setSpeed(abs(_speed));
          break;
          case _S:
              _d = _B;
              myMotor->run(_d);
              myMotor->setSpeed(255);
              delay(50);
              _m->setSpeed(abs(_speed));

              _print(_speed);
          break;
          case _F:
              myMotor->run(_S);
              delay(25);
              _d = _B;
              myMotor->run(_d);
              myMotor->setSpeed(255);
              delay(25);
              _m->setSpeed(abs(_speed));
          break;
        }
      }

      else
            if (_speed == 0)
      {
        _d = _S;
        _m->run(_d);
        //_m.setSpeed(abs(_speed));
      }
    }
};

/*
Adafruit_MotorShield* AFMS;
Adafruit_DCMotor *myMotor;
int _speed;
void setup() {
  // put your setup code here, to run once:
auto _AFMS = Adafruit_MotorShield();
AFMS = &_AFMS;
myMotor = AFMS->getMotor(1);
AFMS->begin();
Serial.begin(9600);
_speed=100;
}
void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available())
  {
    _speed=Serial.parseInt();
    Serial.println(_speed);
    myMotor->setSpeed(255);
    delay(50);
  }
myMotor->setSpeed(_speed);
myMotor->run(FORWARD);
}*/

motor * m;

void setup()
{
 m =new motor(1);
 m->set(255);
 //Serial.begin(9600);
}
  void loop()
  {
    int _speed;
   if (Serial.available())
  {
    _speed=Serial.parseInt();
    Serial.println(_speed);
    m->set(_speed);
  }
}
