#include <AntoIO.h>
#include <DHT.h>
#define DHTPIN 0
#define DHTTYPE DHT22
const char *ssid = "2i";
const char *pass = "HPkyqN4E";
const char *user = "film_1701";
const char *token = "27Ixoxo7Bx7aoQ5bIWif6t4PpeW4elRpamBlU2mE";
const char *thing = "DHT_test";
AntoIO anto(user, token, thing);
DHT dht(DHTPIN,DHTTYPE);
void setup() {
  pinMode(D1,OUTPUT); 
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Anto library version: ");
  Serial.println(anto.getVersion());
  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");
  anto.begin(ssid, pass, messageReceived);
  Serial.println("\nConnected Anto done");
  dht.begin();
  anto.sub("LED_1");
}

void loop() {
  anto.mqtt.loop();
  if (!anto.mqtt.isConnected())
    Serial.println("Disconnected");
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  Serial.print("TEMP: ");
  Serial.println(temp);
  Serial.print("HUMID: ");
  Serial.println(humid);
  if(temp >= 0){
     anto.pub("Temp",temp);           
  }
  if(humid >= 0){
     anto.pub("Humid",humid);
  }
  delay(1000);
}
void messageReceived(String thing, String channel, String payload) {
  Serial.print("Recieved: ");
  Serial.print(thing);
  Serial.print("/");
  Serial.print(channel);
  Serial.print("-> ");
  Serial.println(payload);
  if(channel.equals("LED_1"))
      digitalWrite(D1,(payload == "1")? 1:0);
}
