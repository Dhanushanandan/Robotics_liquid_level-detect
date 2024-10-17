#include <Servo.h>

Servo myservo; //creating a object for the servo library 
int x;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(10);
  pinMode(7,INPUT); //IR sensor 1
  pinMode(4,INPUT); //capacitive sensor
  pinMode(2,INPUT); //IR Sensor 2
  pinMode(8,OUTPUT); //Green LED & Motor 1
  pinMode(12,OUTPUT); //RED LED & Motor 2
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor1 = digitalRead(7);
  if(sensor1 == HIGH){
      digitalWrite(8,LOW);
      delay(1000);
      int capsen= digitalRead(4);
      if(capsen == HIGH){
        digitalWrite(8,LOW);
        delay(1000);
        myservo.write(0);
        delay(1000);
        for(x=0; x<=180; x+=1){
          myservo.write(x);
          delay(5); //controll speed of the motor
        }
        delay(1000);
        int sensor2= digitalRead(2);
        if(sensor2 == HIGH){
          delay(1000);
          myservo.write(0);
          delay(1000);
          digitalWrite(12,HIGH);
          digitalWrite(8,HIGH);
        }
      }else{
        digitalWrite(8,HIGH);
      }

  }else{
    digitalWrite(8,HIGH);
  }

}
