#include <LiquidCrystal.h>
LiquidCrystal lcd(5,6,8,9,10,11);
  
int redled = 2;
int greenled = 7;
int yelloled = 3;
int buzzer = 4;
int sensor = A0;
int sensorclear = 354;
int sensorThresh = 505;


void setup()
{
  pinMode(redled, OUTPUT);
  pinMode(yelloled,OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(sensor,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop()
{
  int analogValue = analogRead(sensor);
  Serial.print(analogValue);
  
  
  if(analogValue<=sensorclear)//green
  {
    digitalWrite(greenled,HIGH);
    digitalWrite(redled,LOW);
    digitalWrite(yelloled, LOW);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("GOOD");
      delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AIR: CLEAR");
      delay(1500);

    
  }
  
  if(analogValue>= 355 && analogValue <= 505){//medium
    digitalWrite(redled,LOW);
    digitalWrite(greenled,LOW);
    digitalWrite(yelloled,HIGH);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AIR: MEDIUM");
      delay(2000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("VERIFY");
      delay(2000);
  }
  if(analogValue>=sensorThresh)//alert
  {
    
    digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
    digitalWrite(yelloled,LOW);
    tone(buzzer,1000,10000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("ALERT");
      delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AIR: TERRIBLE");
      delay(1000);
  }
}
