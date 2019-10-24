#include <Wire.h>                   // เรียก Library
#include <LiquidCrystal_I2C.h>      // เรียก Library LCD
#include <DHT.h>                  // เรียก Library DHT
 
#define DHTPIN D3        // DHT Pin  กำหนดเป็น D3
#define DHTTYPE DHT22   // เรียกใช้DHT 22
int cooling_pin =2; //ประกาศตัวแปร cooling_pin 2 = ขาD4 = GPIO2
              

DHT dht(DHTPIN, DHTTYPE);   // ประกาศตัวแปรคลาส dht
 
LiquidCrystal_I2C lcd(0x27, 16, 2); ประกาศตัวแปร LiquidCrystal_I2C LCD 16x2
void setup()
{
  Serial.begin(9600);     
  dht.begin();            // initial ตัวแปรคลาส dht
  lcd.begin();            // initial ตัวแปรคลาส lcd
  lcd.backlight();        // เปิดไฟ backlight
  pinMode(cooling_pin, OUTPUT); // เซ็ตcooling_pinเป็นoutput
}
 
void loop()
{
  
  delay(2000);                              
  float h = dht.readHumidity();             // อ่านค่าความชื้นด้วยฟังก์ชั่น readHumidity ไปยังตัวแปร h
  float t = dht.readTemperature();          // อ่านค่าอุณหภูมิด้วยฟังก์ชั่น readTemperature ไปยังตัวแปร t
  if (isnan(h) || isnan(t) ) {                 // เช็คตัวแปรทุกตัวมีตัวใดตัวหนึ่งเป็น อนันต์ ถือว่าอ่านค่าไม่สำเร็จ
    Serial.println("Failed to read from DHT sensor!");    // ส่งข้อความออกทาง Serial Monitor ว่าไม่สำเร็จ
    lcd.setCursor(1, 0);            // เซต cursor ไปที่ตัวอักษรที่ 1 บรรทัดที่ 0
    lcd.print("!!!!!!!!!Error!!!!!!!!!"); // ส่งข้อความออกทาง LCD ตำแหน่งที่ระบุด้านบน
    return;                                               // เช็คถ้าอ่านค่าไม่สำเร็จให้เริ่มอ่านใหม่ โดยกระโดดกลับไปยังบรรทัด loop() ใหม่
  }
 
  Serial.print("DHT11 Humidity: ");       
  Serial.print(h); // แสดงค่าความชื้น ทางSerial Monitor
  Serial.print(" %\t\n");                   
  Serial.print("DHT11 Temperature: ");
  Serial.print(t); แสดงค่าอุณหภูมิ ทางSerial Monitor
  Serial.print(" *C \n");
  Serial.print("******************************************************************\n");

  lcd.setCursor(1, 0);                    // เซต cursor ไปที่ตัวอักษรที่ 1 บรรทัดที่ 0
  lcd.print("Temp:");                     // ส่งข้อความออกทาง LCD ตำแหน่งที่ระบุด้านบน
  lcd.print(t);                           // ส่งค่าตัวแปรtออกทางLCD
  lcd.print(" *C");                       
  lcd.setCursor(0, 1);                    
  lcd.print("Humidity:");       
  lcd.print(h);
  lcd.print("%\n");    

  if (t > 31){
    digitalWrite(cooling_pin, HIGH);  // ถ้าอุณหภูมิเกิด31 ให้แผ่นเพลเทียรทำงาน
  }
  else
  {
    digitalWrite(cooling_pin, LOW);
  }
}
