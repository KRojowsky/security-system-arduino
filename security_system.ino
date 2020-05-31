#include <Wire.h> 
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h> 

const byte ROWS = 4; 
const byte COLS = 4; 
int pos = 0;
char k1;

byte rowPins[ROWS] = {5, 4, 3, 2}; 
byte colPins[COLS] = {6, 7, 8, 9}; 

Servo myservo;
 
char keys[ROWS][COLS] = { 
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'%','^','/',' '}
};
 
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 

LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  myservo.attach(10);
  myservo.write(180);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("WPROWADZ PIN:");
}
  
void loop()
{ 
  if(k1 = klawiatura.getKey())
  {
    lcd.setCursor(3, 1);
    lcd.print(k1);

  if(k1 == '1')
  {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("PRAWIDLOWY PIN");
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
      delay(1000);
      for (pos = 180; pos >= 87; pos -= 1) 
       { 
          myservo.write(pos);              
          delay(10);                       
       }

      delay(2000);
      for (pos = 87; pos <= 180; pos += 1)
      { 
          myservo.write(pos);              
          delay(10);                       
      }

      delay(1000);
      lcd.clear();
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      lcd.setCursor(1, 0);
      lcd.print("WPROWADZ PIN:");
  }

  else
  {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("BLEDNY PIN");
      delay(500);

      int iter = 10;
      
      while(iter >= 0)
      {
        tone(13, 4300);  
        delay(150);  
        tone(13, 3500);  
        delay(150);
        
        iter -= 1;
      }
      noTone(13); 

      lcd.clear();

      lcd.setCursor(5,0);
      lcd.print("SYSTEM");
      lcd.setCursor(2,1);
      lcd.print("ZABLOKOWANY");
      
      while(true)
      {
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
        delay(150);
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        delay(150);
      }
  }
  }
}
