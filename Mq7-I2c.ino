#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Substitua 0x27 pelo endereço I2C correto do seu LCD

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
  pinMode(yelloled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  lcd.init(); // Inicializa o LCD
  lcd.backlight(); // Ativa a luz de fundo do LCD (se disponível)
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop()
{
  int analogValue = analogRead(sensor);

  Serial.println(analogValue);

  if (analogValue <= sensorclear)
  {
    digitalWrite(greenled, HIGH);
    digitalWrite(redled, LOW);
    digitalWrite(yelloled, LOW);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("GOOD");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AIR: CLEAR");
    delay(1500);
    /* lcd.clear(); */
  }

  if (analogValue >= 355 && analogValue <= 505)
  {
    digitalWrite(redled, LOW);
    digitalWrite(greenled, LOW);
    digitalWrite(yelloled, HIGH);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AIR: MEDIUM");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("VERIFY");
    delay(2000);
    /* lcd.clear(); */
  }

  if (analogValue >= sensorThresh)
  {
    digitalWrite(redled, HIGH);
    digitalWrite(greenled, LOW);
    digitalWrite(yelloled, LOW);
    tone(buzzer, 1000, 10000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("ALERT");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AIR: TERRIBLE");
    delay(1000);
    /* lcd.clear(); */
  }
}
