#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  
int irPin = 2;
int count = 1;
int speedLimit = 70;  
boolean state = true;
#define POWER_PIN 3 
#define DO_PIN 4     
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
pinMode(irPin, INPUT);
lcd.setCursor(0, 0);
  lcd.print("Count of vech : ");
  lcd.setCursor(0, 1);
  lcd.print("Speed limit : "); 
  pinMode(POWER_PIN, OUTPUT);
}
void loop() {
  digitalWrite(POWER_PIN, HIGH);  
  delay(10);                     
  int rain_state = digitalRead(DO_PIN);
digitalWrite(POWER_PIN, LOW);  
  if (!digitalRead(irPin) && state) {
    count++;
    state = false;
 Serial.print("Count of vehicles: ");
    Serial.println(count);
      delay(100); 
  }
 if (digitalRead(irPin)) {
    state = true;
    delay(100);  
  }
 if (count == 60) {
    count = 1;
    delay(100); 
  }
  for (int i = 1; i <= 60; i++) {
    if (count == i) {
      if (i < 30) {
        speedLimit = 70;
      } else if (i < 60) {
        speedLimit = 50;
      }
      break;
    }
  }
  lcd.setCursor(14, 0);
  lcd.print(count);
  lcd.setCursor(14, 1); 
  lcd.print(speedLimit);
if (rain_state == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Road is wet");
    lcd.setCursor(0, 1);
    lcd.print("Speedlimit:50km      /h");
    delay(100);
  }
else { 
  lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Count of vech : ");
    lcd.setCursor(0, 1);
    lcd.print("Speed limit : ");
  lcd.setCursor(14, 0);  
  lcd.print(count);
lcd.setCursor(14, 1);  
  lcd.print(speedLimit); 
}
}
