#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define BUZZER 8
#define IRPIN 3
#define LDRPIN 6
#define LDR_OUT 13

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float threshold = 34.0;
bool showTemp = true;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(BUZZER, OUTPUT);
  pinMode(IRPIN, INPUT);
  pinMode(LDRPIN, INPUT);
  pinMode(LDR_OUT, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Baby Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();
  int motion = digitalRead(IRPIN);
  int ldrState = digitalRead(LDRPIN);

  if (isnan(temp)) {
    Serial.println("Sensor Error!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error   ");
    return;
  }

  // -------- LDR LOGIC (REVERSED FIX) --------
  if (ldrState == HIGH) {   // reversed condition
    digitalWrite(LDR_OUT, HIGH);
    Serial.println("LDR: Night -> Light ON");
  } else {
    digitalWrite(LDR_OUT, LOW);
    Serial.println("LDR: Day -> Light OFF");
  }

  // -------- TOGGLE DISPLAY --------
  if (showTemp) {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print(" C   ");

    if (temp > threshold) {
      lcd.setCursor(0, 1);
      lcd.print("High Temp!     ");
      Serial.println("ALERT: High Temperature!");
      digitalWrite(BUZZER, HIGH);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Temp Normal    ");
      Serial.println("Temp Normal");
      digitalWrite(BUZZER, LOW);
    }

  } else {
    lcd.setCursor(0, 0);
    lcd.print("Baby Status--  ");

    if (motion == HIGH) {
      lcd.setCursor(0, 1);
      lcd.print("Baby Moving!   ");
      Serial.println("ALERT: Baby Moving!");
      digitalWrite(BUZZER, HIGH);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Baby Safe      ");
      Serial.println("Baby Safe");
      digitalWrite(BUZZER, LOW);
    }
  }

  showTemp = !showTemp;

  delay(2000);
}