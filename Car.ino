#include <hcsr04.h>
#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define rx A1
#define tx A0
#define laser A2
#define tri A3
#define ech A4

SoftwareSerial BTtrans(rx, tx);
AF_DCMotor Lmotor(3);
AF_DCMotor Rmotor(4);
Servo Hor;
Servo Ver;
HCSR04 sonic(tri, ech, 20, 4000);

void BTcontrol();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTtrans.begin(9600);
  BTtrans.setTimeout(100);

  Hor.attach(10);
  Ver.attach(9);
  Hor.write(0);
  Ver.write(0);

  Lmotor.setSpeed(0);
  Lmotor.run(RELEASE);

  Rmotor.setSpeed(0);
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
  if (BTtrans.available())
  {
    char c = BTtrans.read();

    if (c == 'P')
    {
      int Power;

      if (c != '#')
      {
        Power = BTtrans.parseInt();
        Lmotor.setSpeed(Power);
        Rmotor.setSpeed(Power);
        Serial.print(Power);
      }
    }

    if (c == 'H')
    {
      int degHor;

      if (c != '#')
      {
        degHor = BTtrans.parseInt();
        Hor.write(degHor);
        Serial.print(degHor);
      }
    }

    if (c == 'V')
    {
      int degVer;

      if (c != '#')
      {
        degVer = BTtrans.parseInt();
        Ver.write(degVer);
        Serial.print(degVer);
      }
    }

    if (c == 'F')
    {
      Serial.print("Forward");
      Lmotor.run(FORWARD);
      Rmotor.run(FORWARD);

    }

    if (c == 'L')
    {
      Serial.print("Left");
      Lmotor.run(BACKWARD);
      Rmotor.run(FORWARD);
    }

    if (c == 'R')
    {
      Serial.print("Right");
      Lmotor.run(FORWARD);
      Rmotor.run(BACKWARD);
    }

    if (c == 'B')
    {
      Serial.print("Backward");
      Lmotor.run(BACKWARD);
      Rmotor.run(BACKWARD);

      int distance = sonic.distanceInMillimeters();
      BTtrans.print("@");
      BTtrans.print(distance);
      BTtrans.write(13);
      Serial.print(distance);

    }

    if (c == 'S')
    {
      Serial.print("Stop");
      Lmotor.run(RELEASE);
      Rmotor.run(RELEASE);
    }

    if (c == 'O')
    {
      digitalWrite(laser, HIGH);
    }

    if (c == 'P')
    {
      digitalWrite(laser, LOW);
    }
  }
}
