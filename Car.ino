//#include <hcsr04.h>
#include <AFMotor.h>
//#include <SoftwareSerial.h>
#include <Servo.h>

//#define rx A1
//#define tx A0
#define laser A2
#define tri A3
#define ech A4

//SoftwareSerial BTtrans(rx, tx);
AF_DCMotor Lmotor(2);
AF_DCMotor Rmotor(4);
Servo Hor;
Servo Ver;
//HCSR04 sonic(tri, ech, 20, 4000);

bool laserStatus = false;

void BTcontrol();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(100);
  //BTtrans.begin(9600);
  //BTtrans.setTimeout(100);

  Hor.attach(10);
  Ver.attach(9);
  Hor.write(90);
  Ver.write(90);
  //delay(100);
  //Hor.detach();
  //Ver.detach();

  Lmotor.setSpeed(100);
  Lmotor.run(RELEASE);

  Rmotor.setSpeed(100);
  Rmotor.run(RELEASE);

  pinMode(A2, OUTPUT);
  digitalWrite(laser, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  BTcontrol();
}

void BTcontrol()
{
  if (Serial.available())
  {
    char c = Serial.read();

    if (c == 'P')
    {
      int Power;

      Power = Serial.parseInt();
      Lmotor.setSpeed(Power);
      Rmotor.setSpeed(Power);
      Serial.println(Power);

    }
    else if (c == 'H')
    {
      int degHor;

      degHor = Serial.parseInt();

      Hor.write(degHor);



      //Serial.print("ok");
    }
    else if (c == 'V')
    {
      int degVer;

      degVer = Serial.parseInt();

      Ver.write(degVer);

      //Serial.print(degVer);
    }
    else if (c == 'F')
    {
      //Serial.print("Forward");
      Lmotor.run(FORWARD);
      Rmotor.run(FORWARD);

    }
    else if (c == 'L')
    {
      //Serial.print("Left");
      Lmotor.run(BACKWARD);
      Rmotor.run(FORWARD);
    }
    else if (c == 'R')
    {
      //Serial.print("Right");
      Lmotor.run(FORWARD);
      Rmotor.run(BACKWARD);
    }
    else if (c == 'B')
    {
      //Serial.print("Backward");
      Lmotor.run(BACKWARD);
      Rmotor.run(BACKWARD);


      /* while (true)
        {
         if (BTtrans.available())
         {
           c = Serial.read();

           if (c == 'S')
           {
             break;
           }

           int distance = sonic.distanceInMillimeters();
           BTtrans.print("@");
           BTtrans.print(distance);
           BTtrans.write(13);
           Serial.print(distance);

           delay(10);

         }
        }*/

    }
    else if (c == 'S')
    {
      //Serial.print("Stop");
      Lmotor.run(RELEASE);
      Rmotor.run(RELEASE);
    }
    else if (c == 'O')
    {
      laserStatus = !laserStatus;
      digitalWrite(laser, laserStatus);
    }

  }
}
