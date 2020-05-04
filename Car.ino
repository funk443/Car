#include <SoftwareSerial.h>
#include <Servo.h>

#define rx A1
#define tx A0

SoftwareSerial BTtrans(rx, tx);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTtrans.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
