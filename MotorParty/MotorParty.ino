#include <AFMotor.h>
#include <Servo.h>

// DC motor on M1
AF_DCMotor motor1(1); //right
AF_DCMotor motor2(3); //left

void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps
  Serial.println("Motor party!");

  pinMode(3, INPUT_PULLUP);


  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  Serial.println("Motor initialized");
}

void loop() {
  int x = !digitalRead(3);

  Serial.print("Sensor 1: ");
  Serial.print(x);
  delay(1000);

  if (x == HIGH) {
    Serial.print("Bottle Detected");

    
    
    //back
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(500);

    // //turn left
    // motor1.run(FORWARD);
    // motor2.run(RELEASE);
    // delay(550);

    //back
    // motor1.run(BACKWARD);
    // motor2.run(BACKWARD);
    // delay(1300);

    // //stop
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(5000);
    // //move forward
    // motor1.run(FORWARD);
    // motor2.run(FORWARD);
    // delay(1000);

    // //turn right
    // motor1.run(RELEASE);
    // motor2.run(FORWARD);
    // delay(400);

    // motor1.run(FORWARD);
    // motor2.run(FORWARD);
    // delay(500);

    //move forward
    // motor1.run(RELEASE);
    // motor2.run(RELEASE);
    // // delay(1000);

    // //wait for get
    // delay(1000);
  }
}
