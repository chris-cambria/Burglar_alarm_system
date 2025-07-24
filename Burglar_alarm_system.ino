#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIR_PIN 2
#define BUZZER 3
#define LED_ALERT 4
#define RELAY_PIN A1
#define LDR_PIN A3  
// password for disarming the system is 1234#
// for re-enabling the system press A
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {7, 8, 9, 10};
byte colPins[COLS] = {11, 12, 13, A0};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "1234";
String input = "";

bool isArmed = true;
int lightThreshold = 400; 

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_ALERT, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Armed");
  lcd.setCursor(0, 1);
  lcd.print("Light: ----");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (input == password) {
        isArmed = false;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("System Disarmed");
        noTone(BUZZER);
        
        digitalWrite(RELAY_PIN, LOW);
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wrong Password");
        delay(1500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(isArmed ? "System Armed" : "Disarmed");
      }
      input = "";
    } else if (key == '*') {
      input = "";
    } else if (key == 'A' && !isArmed) {
      isArmed = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("System Armed");
      delay(1000);
    } else {
      input += key;
    }
  }

  int lightLevel = analogRead(LDR_PIN);

  // Show live light level
  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  lcd.print(lightLevel);
  lcd.print("   "); 

  if (isArmed && digitalRead(PIR_PIN) == HIGH && lightLevel < lightThreshold) {
    triggerAlarm();
    digitalWrite(LED_ALERT, HIGH);
  } else {
    noTone(BUZZER);
    digitalWrite(LED_ALERT, LOW);
    
    digitalWrite(RELAY_PIN, LOW);
  }

  delay(100);
}

void triggerAlarm() {
  lcd.setCursor(0, 0);
  lcd.print("INTRUDER ALERT");
  tone(BUZZER, 1000);
  digitalWrite(LED_ALERT, HIGH);
  digitalWrite(RELAY_PIN, HIGH);
}
