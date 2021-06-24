#include "SevSeg.h"
SevSeg sevseg;

const int  buttonPin1 = 10;    // the pin that the pushbutton is attached to
const int  buttonPin2 = 11;
int buzzer=12;
int buttonState1 = 0;          // current state of the button
int lastButtonState1 = LOW;    // previous state of the button
int buttonPushCounter1 = 0;    // counter for the number of button presses

int buttonState2 = 0;          // current state of the button
int lastButtonState2 = LOW;    // previous state of the button
int buttonPushCounter2 = 0;    // counter for the number of button presses

long counter = 0;
long max_long_val = 2147483647L;

void setup(){
  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {6, 5, 2 , 3, 4 , 7, 8, 9};
  bool resistorsOnSegments = true; 

  byte hardwareConfig = COMMON_ANODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  pinMode(buzzer, OUTPUT);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  Serial.begin(9600);
  lastButtonState1 = LOW;

}

void loop(){
  buttonState1 = digitalRead(buttonPin1);
  if(buttonState1 == HIGH){
    buttonState1 = LOW;
         digitalWrite(buzzer,LOW);

    }

  else
   buttonState1 = HIGH;

  if(buttonState1 == HIGH){
     Serial.println("on");
     lastButtonState1 = HIGH;
       digitalWrite(buzzer,HIGH);
          delay(500);
                       digitalWrite(buzzer,LOW);
     buttonPushCounter1++;
     if(counter < max_long_val)
       counter++;
     buttonPushCounter1 %= 9;
     sevseg.setNumber(buttonPushCounter1);    
     sevseg.refreshDisplay();     
     delay(2000 - (counter%99));
     }

buttonState2 = digitalRead(buttonPin2);
  if(buttonState2 == HIGH){
    buttonState2 = LOW;
             digitalWrite(buzzer,LOW);

    }

  else
   buttonState2 = HIGH;

  if(buttonState2 == HIGH){
     Serial.println("2-on");
     lastButtonState1 = HIGH;
          digitalWrite(buzzer,HIGH);
          delay(500);
                       digitalWrite(buzzer,LOW);


     buttonPushCounter1--;
     if(counter < max_long_val)
       counter++;
     buttonPushCounter2 %= 9;
     sevseg.setNumber(buttonPushCounter1);    
     sevseg.refreshDisplay();     
     delay(2000 - (counter%99));
     }
} 
  
