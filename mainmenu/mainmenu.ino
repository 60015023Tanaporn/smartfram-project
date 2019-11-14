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
  Serial.print("brightness =");
  Serial.print(ledmap); //โชว์ค่าออกมาเป็น%
  Serial.print("%\n");
  ledmap = map(brightness,0,255,0,99); //เทียบค่าpwm(0-255)ออกมาเป็น%(0-100)
  analogWrite(pin_led,brightness); // output เป็นpwm ใช้ได้ทุกขายกเว้น D0
  
  if(digitalRead(button_up)==LOW){ //ถ้าสถานะปุ่มกดUPเท่ากับLOW(ต่อแบบpull up)แล้วbrightnessน้อยกว่า255
    if (brightness<255){ /
      brightness++,brightness+=12,brightness==255;//ให้brightnessเพิ่มได้ทีละ12 จนเท่ากัมากกว่า255
      delay(150);
    }
  }
  
  if(digitalRead(button_down)==LOW){//ถ้าสถานะปุ่มกดdown เท่ากับLOW(ต่อแบบpullup)แล้วbrightnessมากกกว่า0
    if (brightness>0){
      brightness--,brightness-=12,brightness==0;//ให้brightnessลดลงได้ทีละ12 จนเหลือ0
      delay(150);
    }
  }
  delay(100);

}
