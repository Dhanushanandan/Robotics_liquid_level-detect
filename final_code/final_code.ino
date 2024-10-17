#include <AFMotor.h>
// #include <Servo.h>
// #include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver srituhobby = Adafruit_PWMServoDriver();

#define servo1 0
#define servo2 1
#define servo3 2
#define servo4 3

// DC motor on M1 M2
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(4);

// Servo motor for piston
// Servo pistonServo;

void setup() {
  Serial.begin(9600);  // Set up Serial library at 9600 bps
  Serial.println("******WELCOME******");

  // Set pins 2 and 8 as INPUT for sensors
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(6, INPUT);

  // Initialize servo motor
  // pistonServo.attach(9);
  // pistonServo.write(0);
  // pistonServo.write(-5);

  // Initialize motors
  Serial.println("Motor Release in setup");
  motor1.setSpeed(110);  // Set speed for motor 1
  motor1.run(RELEASE);   // Stop motor 1

  motor2.setSpeed(50);  // Set speed for motor 2
  motor2.run(RELEASE);  // Stop motor 2

  motor3.setSpeed(140);  // Set speed for motor 3
  motor3.run(RELEASE);


  // Serial.begin(9600);
  srituhobby.begin();
  srituhobby.setPWMFreq(60);
  srituhobby.setPWM(servo1, 0, 500);  //max 600 left        min 150 right
  srituhobby.setPWM(servo2, 0, 600);  //max 600 down        min 150 up
  srituhobby.setPWM(servo3, 0, 600);  //max 600 up          min  450 down
  srituhobby.setPWM(servo4, 0, 150);  //max 600 open        min 150 close
  delay(3000);
}

void loop() {
  // Run motors forward
  Serial.println("Motor Forward in loop 1st");
  motor1.run(FORWARD);
  // motor2.run(FORWARD);
  // delay(1000);

  // Read sensors
  int x = !digitalRead(2);  // Read sensor connected to pin 2
  Serial.println("Sensor1 Read " + String(x));

  if (x == HIGH) {
    delay(2900);  // Wait for 1.5 seconds
    Serial.println("Motor release inside 1st sensor high");
    motor1.run(RELEASE);
    // motor2.run(RELEASE);
    // Stop motor 2
    // motor2.run(RELEASE);
    delay(3000);


    // Read sensors2
    int z = digitalRead(6);  // Read sensor connected to pin 2
    Serial.println("Sensor2 Read " + String(z));

    if (x == HIGH && z == LOW) {
      Serial.println("Transfering bottle." + String(2));

      // Move the filled bottle to conveyor belt 2
      // for (int i = 0; i <= 360; i++) {  // Servo movement range
      //   pistonServo.write(i);
      //   delay(10);  // Servo movement speed
      // }
      // delay(3000);
      // pistonServo.write(0);  // Reset piston position
      // delay(3000);


      motor3.run(BACKWARD);
      delay(900);
      motor3.run(FORWARD);
      delay(1500);
      motor3.run(RELEASE);
      delay(950);
      motor3.run(BACKWARD);
      delay(500);
      motor3.run(FORWARD);
      delay(1500);
      motor3.run(RELEASE);
      delay(900);


      motor2.run(FORWARD);
      delay(3200);
      motor2.run(RELEASE);


    } else if (x == HIGH && z == HIGH) {
      motor1.run(FORWARD);
    }
    // Read Third sensor
    int y = !digitalRead(3);  // Read sensor connected to pin 8
    Serial.println("Sensor3 Read " + String(y));

    if (y == HIGH) {
      // delay(3000);
      // motor1.run(FORWARD); // Run motor 1 forward
      // motor2.setSpeed(30);
      // Run motor 2 forward
      // motor1.run(RELEASE);
      // motor2.setSpeed(0);
      motor2.run(RELEASE);

      // motor2.run(FORWARD);
      // motor1.run(FORWARD);
      // delay(5000);
      // motor2.run(RELEASE);

      //Starting
      //turn to place
      for (int S1value = 500; S1value >= 100; S1value--) {
        srituhobby.setPWM(servo1, 0, S1value);
        delay(10);
      }

      //open the clip
      for (int S4value = 150; S4value <= 400; S4value++) {
        srituhobby.setPWM(servo4, 0, S4value);
        delay(10);
      }

      //move foward
      for (int S3value = 600; S3value >= 500; S3value--) {
        srituhobby.setPWM(servo3, 0, S3value);
        delay(10);
      }

      //close the clip after grep
      for (int S4value = 400; S4value >= 150; S4value--) {
        srituhobby.setPWM(servo4, 0, S4value);
        delay(10);
      }

      //lift up the item
      for (int S2value = 600; S2value >= 150; S2value--) {
        srituhobby.setPWM(servo2, 0, S2value);
        delay(10);
      }
      //move to place the item
      for (int S1value = 150; S1value <= 300; S1value++) {
        srituhobby.setPWM(servo1, 0, S1value);
        delay(10);
      }
      //lift down the item
      for (int S2value = 150; S2value <= 600; S2value++) {
        srituhobby.setPWM(servo2, 0, S2value);
        delay(10);
      }

      //drop the item
      for (int S4value = 150; S4value <= 400; S4value++) {
        srituhobby.setPWM(servo4, 0, S4value);
        delay(10);
      }

      //return to normal position
      for (int S3value = 500; S3value <= 600; S3value++) {
        srituhobby.setPWM(servo3, 0, S3value);
        delay(10);
      }

      //close the clip
      for (int S4value = 400; S4value >= 150; S4value--) {
        srituhobby.setPWM(servo4, 0, S4value);
        delay(10);
      }

      //return to the starting place
      for (int S1value = 150; S1value <= 600; S1value++) {
        srituhobby.setPWM(servo1, 0, S1value);
        delay(10);
      }
    }

  } else if (x == LOW) {
    // Serial.println("Motor run in else");
    // motor1.setSpeed(200); // Set speed for motor 1
    // motor2.setSpeed(200); // Set speed for motor 2
    motor1.run(FORWARD);  // Run motor 1 forward
    // motor2.run(FORWARD);
    // motor2.run(FORWARD); // Run motor 2 forward
  }
}
