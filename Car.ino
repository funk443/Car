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

  Lmotor.setSpeed(200);
  Lmotor.run(RELEASE);

  Rmotor.setSpeed(200);
  Rmotor.run(RELEASE);
}

void loop() {
  // put your main code here, to run repeatedly:

}
