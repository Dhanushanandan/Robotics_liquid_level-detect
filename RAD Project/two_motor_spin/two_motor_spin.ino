#include <Servo.h>

Servo x;

const int motorPin1 = 8;      // IN1 on the L293D
const int motorPin2 = 7;      // IN2 on the L293D
const int enablePin1 = 10;    // EN1 on the L293D (changed from 9)
const int motorPin3 = 3;      // IN3 on the L293D
const int motorPin4 = 4;      // IN4 on the L293D
const int enablePin2 = 11;    // EN2 on the L293D (added for second motor)
const int irSensorPin1 = 2;   // Output pin of the first IR sensor
const int irSensorPin2 = 12;  // Output pin of the second IR sensor
const int irSensorPin3 = 13;  // Output pin of the third IR sensor

void setup() {
  x.attach(9);  // Servo attached to pin 9
  x.write(0);   // Initialize servo position to 0

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);
  pinMode(irSensorPin3, INPUT);

  // Initialize motors as stopped
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  analogWrite(enablePin1, 0);
  analogWrite(enablePin2, 0);
}

void loop() {
  int sensorValue1 = digitalRead(irSensorPin1);  // Object detect sensor

  if (sensorValue1 == HIGH) {  // Assuming HIGH means obstacle detected
    // Stop the motors
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    analogWrite(enablePin1, 0);
    analogWrite(enablePin2, 0);

    int sensorValue2 = digitalRead(irSensorPin2);  // Level detect sensor

    if (sensorValue2 == HIGH) {
      for (int i = 0; i <= 180; i++) {  // Servo movement range
        x.write(i);
        delay(10);
      }

      int sensorValue3 = digitalRead(irSensorPin3);  // Next sensor detect

      if (sensorValue3 == HIGH) {
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        analogWrite(enablePin1, 255);  // Full speed
        analogWrite(enablePin2, 255);  // Full speed
      }
    } else {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      analogWrite(enablePin1, 255);  // Full speed
      analogWrite(enablePin2, 255);  // Full speed
    }
  } else {
    // Spin the motors
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    analogWrite(enablePin1, 255);  // Full speed
    analogWrite(enablePin2, 255);  // Full speed
  }
}
