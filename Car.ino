#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define rx A1
#define tx A0

SoftwareSerial BTtrans(rx, tx);
AF_DCMotor Lmotor(4);
AF_DCMotor Rmotor(5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTtrans.begin(9600);
  BTtrans.setTimeout(100);

  Lmotor.setSpeed(0);
  Lmotor.run(RELEASE);

  Rmotor.setSpeed(0);
  Rmotor.run(RELEASE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(BTtrans.available())
  {
    char c = BTtrans.read();
    
    if(c == 'P')
    {
      int Power;

      Power = BTtrans.parseInt();

      
      if(c != '#')
      {
        Lmotor.setSpeed(Power);
        Rmotor.setSpeed(Power);
        Serial.print(Power);
      }
    }
  }

  if(Serial.available())
  {
    char c = Serial.read();
    BTtrans.print(c);
  }
}
