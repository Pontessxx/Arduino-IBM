#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 6, 8, 9, 10, 11);

int redled = 2;
int greenled = 7;
int yellowled = 3;
int buzzer = 4;
int sensor = A0;
int sensorclear = 100; // Valor de referência para ar limpo
int sensorThresh = 800; // Valor de referência para alerta

void setup()
{
  pinMode(redled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  int analogValue = analogRead(sensor);
  Serial.print(analogValue);

  if (analogValue <= sensorclear) // Ar limpo (verde)
  {
    digitalWrite(greenled, HIGH);
    digitalWrite(redled, LOW);
    digitalWrite(yellowled, LOW);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("BOM");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AR: LIMPO");
    delay(1500);
  }

  if (analogValue > sensorclear && analogValue < sensorThresh) // Qualidade média do ar (amarelo)
  {
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);
    digitalWrite(yellowled, HIGH);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AR: MEDIO");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("VERIFICAR");
    delay(2000);
  }

  if (analogValue >= sensorThresh) // Alerta de ar ruim (vermelho)
  {
    digitalWrite(redled, HIGH);
    digitalWrite(greenled, LOW);
    digitalWrite(yellowled, LOW);
    tone(buzzer, 1000, 10000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("ALERTA");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AR: PESSIMO");
    delay(1000);
  }
}
