// A useful class for controlling a servo motor on the robot using the adafruit shield.

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define _print //Serial.println

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

	// This is the constructor of the class
	// Takes an integer from 1 to 4 (the channel number)
   public: motor(short port)
    {
      _speed=0;
      AFMS = new Adafruit_MotorShield();
      myMotor = AFMS->getMotor(port);
      AFMS->begin();
      //Serial.begin(9600);
     // Serial.println("Constructor worked");
    }
    ~motor() // the destructor
    {
      delete AFMS;
    }

	// sets the speed
	// the sign of __speed decides the direction
	// 	Min is -255 (full speed reverse) max is 255 (full speed forward)
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
