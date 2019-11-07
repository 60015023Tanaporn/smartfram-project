#include <Wire.h>                   // เรียก Library
#include <LiquidCrystal_I2C.h>      // เรียก Library LCD
#include <DHT.h>                  // เรียก Library DHT
 
#define DHTPIN D3        // DHT Pin  กำหนดเป็น D3
#define DHTTYPE DHT22   // เรียกใช้DHT 22
int cooling_pin =2; //ประกาศตัวแปร cooling_pin 2 = ขาD4 = GPIO2
              

DHT dht(DHTPIN, DHTTYPE);   // ประกาศตัวแปรคลาส dht
 
LiquidCrystal_I2C lcd(0x27, 16, 2); //ประกาศตัวแปร LiquidCrystal_I2C LCD 16x2
void setup() {
  Serial.begin(9600);   
  dht.begin();            // initial ตัวแปรคลาส dht
  lcd.begin();            // initial ตัวแปรคลาส lcd
  lcd.backlight();        // เปิดไฟ backlight
}

void loop() {
  // put your main code here, to run repeatedly:

}
