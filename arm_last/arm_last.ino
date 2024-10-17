

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver srituhobby = Adafruit_PWMServoDriver();

#define servo1 0
#define servo2 1
#define servo3 2
#define servo4 3


void setup() {
  Serial.begin(9600);
  srituhobby.begin();
  srituhobby.setPWMFreq(60);
  srituhobby.setPWM(servo1, 0, 500);  //max 600 left        min 150 right
  srituhobby.setPWM(servo2, 0, 600);  //max 600 down        min 150 up
  srituhobby.setPWM(servo3, 0, 600);  //max 600 up          min  450 down
  srituhobby.setPWM(servo4, 0, 150);  //max 600 open        min 150 close
  delay(3000);
}





void loop() {

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
