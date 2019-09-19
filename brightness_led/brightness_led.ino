#include <Wire.h>  
int pin_led = 14; //GPIO14 =D5
int button_up =12; //GPIO12=D6
int button_down = 13;//GPIO13 =D7
int brightness=0; //ค่าpwm
int ledmap;  // ตัวแปรไว้แปลงค่าเป็น%
void setup() {
  Serial.begin(9600);
  pinMode(pin_led,OUTPUT);
  pinMode(button_up,INPUT);
  pinMode(button_down,INPUT);

}

void loop() {
  Serial.print("brightness =");
  Serial.print(ledmap); //โชว์ค่าออกมาเป็น%
  Serial.print("%\n");
  ledmap = map(brightness,0,255,0,99); //เทียบค่าpwm(0-255)ออกมาเป็น%(0-100)
  analogWrite(pin_led,brightness); // output เป็นpwm ใช้ได้ทุกขายกเว้น D0
  
  if(digitalRead(button_up)==LOW){ //ถ้าสถานะปุ่มกดUP เท่ากับLOW(ต่อแบบpull up)แล้วbrightnessน้อยกว่า255
    if (brightness<255){ /
      brightness++,brightness+=12,brightness==255;//ให้brightnessเพิ่มได้ทีละ12 จนเท่ากับมากกว่า255
      delay(150);
    }
  }
  
  if(digitalRead(button_down)==LOW){//ถ้าสถานะปุ่มกดdown เท่ากับLOW(ต่อแบบpull up)แล้วbrightnessมากกกว่า0
    if (brightness>0){
      brightness--,brightness-=12,brightness==0;//ให้brightnessลดลงได้ทีละ12 จนเหลือ0
      delay(150);
    }
  }
  delay(100);

 
}
