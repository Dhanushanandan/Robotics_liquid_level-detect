#include <Servo.h>

Servo myservo;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(10);
  myservo.write(0);
  // pinMode(7,INPUT);
}

void loop() {

    myservo.write(360);
  delay(800);
  myservo.write(180);

  delay(500);

  myservo.write(0);
  delay(800);
  myservo.write(90);
  
}
