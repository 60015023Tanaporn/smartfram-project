/****************
  คอร์ส การใช้งาน ESP8266 ฉบับจับมือทำ สำหรับผู้เริ่มต้น
  https://www.facebook.com/IOTProductDesign/
****************/
#include <Wire.h>                   // include file .h เพื่อใช้งาน Library
#include <LiquidCrystal_I2C.h>      // include file .h เพื่อใช้งาน Library LCD
#include "DHT.h"                    // include file .h เพื่อใช้งาน Library DHT
 
#define DHTPIN D3         // DHT Pin                      // DHT Pin  กำหนดเป็น D3
//#define DHTTYPE DHT11     // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321     หากใช้ DHT22 ให้ uncomment บรรทัดนี้ แล้ว comment บรรทัด DHT11 ออกแทน
//#define DHTTYPE DHT21   // DHT 21 (AM2301)              หากใช้ DHT21 ให้ uncomment บรรทัดนี้ แล้ว comment บรรทัด DHT11 ออกแทน

DHT dht(DHTPIN, DHTTYPE);                                 // ประกาศตัวแปรคลาส dht
 
LiquidCrystal_I2C lcd(0x27, 16, 2); // ถ้าจอไม่แสดงผล ให้ลองเปลี่ยน 0x3F เป็น 0x27 ประกาศตัวแปร LiquidCrystal_I2C LCD 16x2
void setup()
{
  Serial.begin(9600);     // เซต Baud rate ของ Serial Port เป็น 9600 ที่ใช้สำหรับ Serial Monitor
  dht.begin();            // initial ตัวแปรคลาส dht
  
  lcd.begin();            // initial ตัวแปรคลาส lcd
  lcd.backlight();        // เปิดไฟ backlight
}
 
void loop()
{
  
  delay(2000);                              // หน่วงเวลา 2 วินาทีให้เซนเซอร์ทำงาน
  float h = dht.readHumidity();             // อ่านค่าความชื้นด้วยฟังก์ชั่น readHumidity ไปยังตัวแปร h
  float t = dht.readTemperature();          // อ่านค่าอุณหภูมิด้วยฟังก์ชั่น readTemperature ไปยังตัวแปร

 
  
  if (isnan(h) || isnan(t) || isnan(f)) {                 // เช็คตัวแปรทุกตัวมีตัวใดตัวหนึ่งเป็น อนันต์ ถือว่าอ่านค่าไม่สำเร็จ
    Serial.println("Failed to read from DHT sensor!");    // ส่งข้อความออกทาง Serial Monitor พร้อมขึ้นบรรทัดใหม่
    return;                                               // เช็คถ้าอ่านค่าไม่สำเร็จให้เริ่มอ่านใหม่ โดยกระโดดกลับไปยังบรรทัด loop() ใหม่
  }
 
  Serial.print("DHT11 Humidity: ");       // ส่งข้อความออกทาง Serial Monitor
  Serial.print(h);
  Serial.print(" %\t");                   // \t คือการใช้ Tab จะเว้นระยะห่างตัวอักษรเหมือนใช้โปรแกรมพิมพ์ Word ทั่วไป
  Serial.print("DHT11 Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");


  lcd.setCursor(1, 0);                    // เซต cursor ไปที่ตัวอักษรที่ 1 บรรทัดที่ 0
  lcd.print("Temp ");                     // ส่งข้อความออกทาง LCD ตำแหน่งที่ระบุด้านบน
  lcd.print(t);                           
  lcd.print(" *C");                       
  lcd.setCursor(0, 1);                    // เซต cursor ไปที่ตัวอักษรที่ 0 บรรทัดที่ 1
  lcd.print("DHT11 Humidity: ");       // ส่งข้อความออกทาง Serial Monitor
  lcd.print(h);
  lcd.print(" %\t");          // ส่งข้อความออกทาง LCD ตำแหน่งที่ระบุด้านบน
}
