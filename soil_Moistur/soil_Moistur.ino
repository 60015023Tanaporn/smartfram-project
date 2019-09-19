int pin_pump = 15;
void setup() {
   Serial.begin(9600);
   pinMode(pin_pump,OUTPUT);
}

void loop() {
  int val_moistur = analogRead(A0);//อ่านค่าความชื้นในดินจากA0
  Serial.println(val_moistur);
  delay(1000);
  if (val_moistur<500){ //ถ้าค่าความชื้นในดินน้อยกว่า500ให้ปั๊มน้ำทำงาน
    digitalWrite(pin_pump,HIGH);
  }
  else{
    digitalWrite(pin_pump,LOW);
  }

}
