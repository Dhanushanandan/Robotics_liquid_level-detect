#include <EEPROM.h>
#include <AFMotor.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Motor setup
AF_DCMotor motor1(1, MOTOR12_1KHZ);  // Motor #1
AF_DCMotor motor2(2, MOTOR12_1KHZ);  // Motor #2
AF_DCMotor motor3(3, MOTOR34_1KHZ);  // Motor #3
AF_DCMotor motor4(4, MOTOR34_1KHZ);  // Motor #4

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 100

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
SoftwareSerial BT(0, 1);

Servo myServo;

bool goesRover = false;
bool updateMemory = false;
int distanceF = MAX_DISTANCE;
int distanceR = 0;
int distanceL = 0;
int i = 200;            // Motor speed
int j = 300;            // Turn angle
int k = 0;
int range;
int addr = 0;
int addr_Start = 1;
int addr_End = 0;
char cmd;

void setup() {
  BT.begin(9600);
  myServo.attach(9);  // Attach the servo to pin 10
  myServo.write(90);   // Set servo to 90 degrees

  distanceF = readPing();
  delay(2000);
  cmd = '9';
  range = MAX_DISTANCE - 20;
  delay(100);
  k = EEPROM.read(200);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

int readPing() {
  int cm = sonar.ping_cm();
  delay(200);
  if (cm == 0) {
    cm = range;
  }
  return cm;
}

void goBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

  motor1.setSpeed(i + 3);
  motor2.setSpeed(i - 27);
  motor3.setSpeed(i + 3);
  motor4.setSpeed(i - 27);
  delay(400);
  Stop();
}

void goForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  motor1.setSpeed(i);
  motor2.setSpeed(i - 25);
  motor3.setSpeed(i);
  motor4.setSpeed(i - 25);
  delay(1000);
  Stop();
}

void goSmart() {
  while (goesRover && cmd == 's') {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);

    motor1.setSpeed(i);
    motor2.setSpeed(i - 26);
    motor3.setSpeed(i);
    motor4.setSpeed(i - 26);
    delay(100);
    distanceF = readPing();
    delay(100);

    if (distanceF < range - 50) {
      Stop();
      goesRover = false;
      goBackward();
      takeTurn();
      break;
    }
  }
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);

  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  delay(j);
  Stop();
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);

  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  delay(j);
  Stop();
}

void takeTurn() {
  j = 100;
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if (distanceR >= distanceL) {
    while (distanceF < range) {
      turnRight();
      distanceF = readPing();
      if (distanceF >= range) {
        goesRover = true;
        goSmart();
        break;
      }
    }
  } else {
    while (distanceF < range) {
      turnLeft();
      distanceF = readPing();
      if (distanceF >= range) {
        goesRover = true;
        goSmart();
        break;
      }
    }
  }
}

int lookRight() {
  myServo.write(0);
  int distanceR = readPing();
  delay(400);
  myServo.write(90);
  return distanceR;
}

int lookLeft() {
  myServo.write(180);
  int distanceL = readPing();
  delay(400);
  myServo.write(90);
  return distanceL;
}

void memory_IN() {
  EEPROM.update(addr, cmd);
  EEPROM.write(addr_Start, addr);
  addr++;
}

void goPath() {
  for (addr = addr_Start; addr <= addr_End; addr++) {
    cmd = EEPROM.read(addr);
    switch (cmd) {
      case 'f':
        goForward();
        delay(50);
        break;
      case 'b':
        goBackward();
        delay(50);
        break;
      case 'r':
        j = 170 + k;
        Stop();
        turnRight();
        break;
      case 'l':
        j = 170 + k;
        Stop();
        turnLeft();
        break;
      case 'u':
        j = 335 + k;
        Stop();
        turnRight();
        break;
      case 'v':
        j = 335 + k;
        Stop();
        turnLeft();
        break;
      default:
        // Handle unknown commands if necessary
        break;
    }
  }
}

void returnPath() {
  j = 640 + k;
  turnRight();
  Stop();
  j = 100;

  for (addr = addr_End; addr >= addr_Start; addr--) {
    cmd = EEPROM.read(addr);
    switch (cmd) {
      case 'f':
        goForward();
        delay(50);
        break;
      case 'b':
        goBackward();
        delay(50);
        break;
      case 'l':
        j = 170 + k;
        Stop();
        turnRight();
        break;
      case 'r':
        j = 170 + k;
        Stop();
        turnLeft();
        break;
      case 'v':
        j = 335 + k;
        Stop();
        turnRight();
        break;
      case 'u':
        j = 335 + k;
        Stop();
        turnLeft();
        break;
      default:
        // Handle unknown commands if necessary
        break;
    }
  }
}

void memory_OUT() {
  goPath();
  delay(10000);
  returnPath();
}

void loop() {
  while (BT.available()) {
    char cmd = BT.read(); // Read the incoming command

    switch (cmd) {
      case '1':
        BT.println("Trace Path for Room-1");
        updateMemory = true;
        addr = 1;
        addr_Start = 0;
        i = 180;
        break;

      case '2':
        BT.println("Trace Path for Room-2");
        updateMemory = true;
        addr = 51;
        addr_Start = 50;
        i = 180;
        break;

      case '3':
        BT.println("Trace Path for Room-3");
        updateMemory = true;
        addr = 101;
        addr_Start = 100;
        i = 180;
        break;

      case '4':
        BT.println("Go Room-1");
        updateMemory = false;
        i = 175;
        addr_End = EEPROM.read(0);
        addr_Start = 1;
        memory_OUT();
        break;

      case '5':
        BT.println("Go Room-2");
        updateMemory = false;
        i = 175;
        addr_End = EEPROM.read(50);
        addr_Start = 51;
        memory_OUT();
        break;

      case '6':
        BT.println("Go Room-3");
        updateMemory = false;
        i = 175;
        addr_End = EEPROM.read(100);
        addr_Start = 101;
        memory_OUT();
        break;

      case '7':
        k += 1;
        BT.println(k);
        EEPROM.write(200, k);
        break;

      case '8':
        k -= 1;
        BT.println(k);
        EEPROM.write(200, k);
        break;

      case 'z':
        BT.println("End of TracePath");
        updateMemory = false;
        break;

      case 's':
        BT.println("Go Smart");
        goesRover = true;
        j = 100;
        goSmart();
        break;

      case 'f':
        BT.println("Go Forward");
        goForward();
        if (updateMemory) {
          memory_IN();
        }
        break;

      case 'b':
        BT.println("Go Backward");
        goBackward();
        if (updateMemory) {
          memory_IN();
        }
        break;

      case 'r':
        BT.println("Turn Right 45D");
        j = 170;
        turnRight();
        if (updateMemory) {
          memory_IN();
        }
        break;

      case 'l':
        BT.println("Turn Left 45D");
        j = 170;
        turnLeft();
        if (updateMemory) {
          memory_IN();
        }
        break;

      case 'u':
        BT.println("Turn Right 90D");
        j = 340;
        turnRight();
        if (updateMemory) {
          memory_IN();
        }
        break;

      case 'v':
        BT.println("Turn Left 90D");
        j = 340;
        turnLeft();
        if (updateMemory) {
          memory_IN();
        }
        break;

      case 'm':
        i = 250;
        BT.println("Speed set to ");
        BT.print(i);
        break;

      case 'n':
        i = 180;
        BT.println("Speed set to ");
        BT.print(i);
        break;

      default:
        BT.println("Unknown Command");
        break;
    }
  }
}