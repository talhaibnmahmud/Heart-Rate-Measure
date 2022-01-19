#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Setting Pins
const int sensorPin = A3;
const int buttonPin = 8;

// Global Values
int value = 0, count = 0;
bool wait = false;

// Initializing LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  // Setting Pin Modes
  pinMode(sensorPin, INPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);

  // Setting Serial Monitor
  Serial.begin(9600);
  Serial.println("Monitoring...");

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-Pulse  Monitor-");
  lcd.setCursor(0, 1);
  lcd.print("Place ur Finger!");
}

void loop() {
  if (!wait)
  {
    // Initial delay
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("-Pulse  Monitor-");
    lcd.setCursor(0, 1);
    lcd.print("Press the Button");
    wait = true;
  }

  if (digitalRead(buttonPin) == 0)
  {
    bool condition = true;
    const int cut_value = 400;
    const int measureTime = 15000;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Please Wait");
    lcd.setCursor(0, 1);
    lcd.print("Measuring......");

    unsigned long startTime = millis();
    unsigned long endTime = startTime + measureTime;

    while (1) {
      if (millis() > endTime) {
        // Final Value
        int t_count = count * 4;

        Serial.print("Value = ");
        Serial.print(t_count);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your Heart Rate:");
        lcd.setCursor(0, 1);
        lcd.print(t_count);
        lcd.print(" BPM");

        break;
      }

      value = analogRead(sensorPin);
      Serial.println(value);

      if (value > cut_value && condition) {
        count++;
        condition = false;

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Please Wait");
        lcd.setCursor(0, 1);
        lcd.print("Measuring..");
      }

      if (!condition && value < cut_value) {
        condition = true;

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Please Wait");
        lcd.setCursor(0, 1);
        lcd.print("Measuring....");
      }
    }
    while (1);
  }
}
