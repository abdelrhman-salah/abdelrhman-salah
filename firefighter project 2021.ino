                                                   //project_level_2_Electrical_Engneering_FireFighter_Robot 
#include <AFMotor.h> //deifine motor sheild 
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
//Define variable
int rec;    //Define BLUTOOTH
int Fsensor = A5; //Define FLAME SENSOR
int fan1 = A4;
int fan2 = A3;
int readingF;

void setup() {
   pinMode(Fsensor, INPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    Serial.begin(9600);
}
void loop() {
  readingF= digitalRead(Fsensor); //Define analoge read for FLAME SENSOR
  if (Serial.available()>0){
    rec = Serial.read();
    Serial.println(rec);
  }
  if(readingF==HIGH){   //there is no fire 
    analogWrite(A2,0);
    digitalWrite(A4,LOW);
    digitalWrite(A3,LOW);
  }
  if(readingF==LOW){  //flame sensor read fire 
    digitalWrite(A1, HIGH); //buzzer work
    delay(100);
    digitalWrite(A1, LOW);
    digitalWrite(A1, HIGH);
    delay(100);
    digitalWrite(A1, LOW);
    analogWrite(A2, 200);
    digitalWrite(A3, LOW); //fan work 
    digitalWrite(A4, HIGH);
    delay(1000); //delay for fan 
  }
  if (rec==1 ){    //MOVE FORWARD WITH BLUTOOTH
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    motor3.setSpeed(255);
    motor4.setSpeed(255);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
  }
  else if (rec==2 ){  // move backword WITH BLUTOOTH
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    motor3.setSpeed(255);
    motor4.setSpeed(255);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }
  else if (rec==3 ){   //turning left  WITH BLUTOOTH
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor3.setSpeed(255);
    motor4.setSpeed(255);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    
  }
  else if (rec==4 ){   // turning right WITH BLUTOOTH
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    motor3.setSpeed(0);
    motor4.setSpeed(0);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
  else if (rec==5){      // RELEASE motor
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor3.setSpeed(0);
    motor4.setSpeed(0);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
}
