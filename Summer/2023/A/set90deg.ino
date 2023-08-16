#include <Servo.h>
#define SERVO_PIN 8 // attach pwm
Servo myServo; //creating a servo object (any custom name could be used)

void setup() {
  // put your setup code here, to run once:
  myServo.attach(SERVO_PIN); 
  myServo.write(90);  

}

void loop() {
  // put your main code here, to run repeatedly:

}
