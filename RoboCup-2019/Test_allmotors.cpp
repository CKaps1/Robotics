// this is a test of the robot with all the motors. It uses code from servo.cpp (pasted below)

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
   public: motor(short port)
    {
      _speed=0;
      AFMS = new Adafruit_MotorShield();
      myMotor = AFMS->getMotor(port);
      AFMS->begin();
      //Serial.begin(9600);
     // Serial.println("Constructor worked");
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

motor* m1,*m2,*m3;
int d = 255;

void setup() {
  // put your setup code here, to run once:
 m1 = new motor(1);
 m2 = new motor(2);
 m3 = new motor(3);

}


void loop() {
  // put your main code here, to run repeatedly:
//d *= -1;
   m1->set(d);
   m2->set(-d);
  // m2->myMotor->run(BACKWARD);
 // m2->myMotor->setSpeed(255);
 // m3->set(d);
  //qm2->set(d);
  //delay(5000);
}
