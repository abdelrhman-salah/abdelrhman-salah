#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo;
#define HC05 Serial2
char t;
#define Flame A6

int sensorReading;
int range,oldrange = 0;
const int sensorMin = 0;   //sensorminimum
const int sensorMax =1023; //sensormaximum
int buzzer = 10;
int relay1 = 11;
int relay2 = 12;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

#define Password_Lenght 5 // Give enough room for six chars + NULL char

int pos = 0;    // variable to store the servo position

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "3579";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
bool door = true;

byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

void setup()
{
  
  Serial.begin(9600);
  HC05.begin(9600);
  myservo.attach(9);
  myservo.write(50);
  pinMode(relay1, OUTPUT); 
  pinMode(relay2, OUTPUT); 
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("--Introdaction--");
  lcd.setCursor(0, 1);
  lcd.print("--Team project--");
  delay(3000);
  lcd.clear();
  digitalWrite(relay1, HIGH);  
  digitalWrite(relay2, HIGH);
}

void loop()
{
sensorReading= analogRead(Flame); //Define analoge read for FLAME SENSOR
  range = map (sensorReading,sensorMin,sensorMax,0,4);
  if (range ==0 && range !=oldrange)
  {
   digitalWrite(buzzer, HIGH);   
  delay(100);            
  digitalWrite(buzzer, LOW);  
  delay(100);
  digitalWrite(buzzer, HIGH);   
  delay(100);            
  digitalWrite(buzzer, LOW);  
  delay(100);
  digitalWrite(buzzer, HIGH);   
  delay(100);            
  digitalWrite(buzzer, LOW);  
  delay(100);
  digitalWrite(buzzer, HIGH);   
  delay(100);            
  digitalWrite(buzzer, LOW);  
  delay(100);
  digitalWrite(buzzer, HIGH);   
  delay(200);            
  digitalWrite(buzzer, LOW);  
  delay(100);
  digitalWrite(buzzer, HIGH);   
  delay(100);            
  digitalWrite(buzzer, LOW);  
  delay(100);
  digitalWrite(buzzer, HIGH);   
  delay(100);            
  digitalWrite(buzzer, LOW);  
  delay(100);
  digitalWrite(buzzer, HIGH);   
  delay(100);            
  digitalWrite(buzzer, LOW);  
  delay(100);
  digitalWrite(buzzer, HIGH);   
  delay(100);            
  digitalWrite(buzzer, LOW);  
  delay(100);
  digitalWrite(buzzer, HIGH);   
  delay(100);            
  digitalWrite(buzzer, LOW);  
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("There is A Fire!!");
  delay(3000);
  lcd.clear();
      oldrange = range;
  }
  else if (range > 0 && range <3 && range  != oldrange)
  {
            
  digitalWrite(buzzer, LOW);  
    Serial.write("*Distant Fire*");
    oldrange = range;
  }
 else if(range== 3 &&range != oldrange){
      
  digitalWrite(buzzer, LOW);  
     Serial.write("No Fire");
    oldrange = range; 
}
if(HC05.available()> 0){
  t = HC05.read();
  Serial.write(t);
  Serial.println(t);
}
if(t == '1'){            //CLOSED DOOR
  digitalWrite(relay1, LOW);
   lcd.setCursor(0, 1);
  lcd.print("LIGHT-1 ON");
  delay(3000);
  lcd.clear();

}

else if(t == 'A'){      //OPEN DOOR
   digitalWrite(relay1, HIGH);
   lcd.setCursor(0, 1);
  lcd.print("LIGHT-1 OFF");
  delay(3000);
  lcd.clear();
}
else if(t == '2'){      //OPEN DOOR
   digitalWrite(relay2, LOW);
   lcd.setCursor(0, 1);
  lcd.print("LIGHT-2 ON");
  delay(3000);
  lcd.clear();
}
else if(t == 'B'){      //OPEN DOOR
   digitalWrite(relay2, HIGH);
   lcd.setCursor(0, 1);
  lcd.print("LIGHT-2 OFF");
  delay(3000);
  lcd.clear();
}
else if(t == '3'){      //OPEN DOOR
           myservo.write(115);
   lcd.setCursor(0, 1);
  lcd.print("Door is OPEN");
  delay(3000);
  lcd.clear();
}
else if(t == 'C'){      //OPEN DOOR
       myservo.write(50);
   lcd.setCursor(0, 1);
  lcd.print("Door is close");
  delay(3000);
  lcd.clear();
}
delay(100);

  if (door == 0)
  {
    customKey = customKeypad.getKey();
    if (customKey == '#')

    {
      lcd.clear();
      lcd.print("  Door is close");
      digitalWrite(buzzer, HIGH);   
  delay(200);            
  digitalWrite(buzzer, LOW);  
  delay(200);
   myservo.write(50);
      delay(3000);
      door = 1;
    }
  }

  else Open();
}

void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}


void Open()
{
  lcd.setCursor(0, 0);
  lcd.print("-Enter Password-");
  
  customKey = customKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    int i;
for( i = 1; i <= 1; i++ )
{
  digitalWrite(buzzer, HIGH);   
  delay(50);            
  digitalWrite(buzzer, LOW);  
  delay(50);      
}  

    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count, 1); // move cursor to show each new char
    lcd.print("*_"); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
    {
      lcd.clear();
      lcd.print("  Door is Open");
       digitalWrite(buzzer, HIGH);   
  delay(70);            
  digitalWrite(buzzer, LOW);  
  delay(70); 
         myservo.write(115);

      door = 0;
    }
    else
    {
      lcd.clear();
      lcd.print("-Wrong Password-");
        digitalWrite(buzzer, HIGH);   
  delay(40);            
  digitalWrite(buzzer, LOW);  
  delay(40); 
  digitalWrite(buzzer, HIGH);   
  delay(40);            
  digitalWrite(buzzer, LOW);  
  delay(40); 
  digitalWrite(buzzer, HIGH);   
  delay(40);            
  digitalWrite(buzzer, LOW);  
  delay(40); 
  digitalWrite(buzzer, HIGH);   
  delay(40);            
  digitalWrite(buzzer, LOW);  
  delay(40); 
         myservo.write(50);

      delay(1000);
      door = 1;
    }
    clearData();
  }



}
