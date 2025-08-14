#include <Servo.h>

int motor1pin1 = 2;
int motor1pin2 = 3;

Servo myServo;  // create servo object

void setup() {
  // Setup for DC motor
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  // Setup for Servo motor
  myServo.attach(9);  // attach the signal pin of servo to pin 9
}

void loop() {
  // DC Motor forward
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

   // Servo move sequence
  myServo.write(0);
  delay(10000);
  myServo.write(160);
  delay(1000);
 

  
}