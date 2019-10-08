#include <AntoIO.h>
const char *ssid = "Aomsin";
const char *pass = "aom1234567890";
const char *user = "SARUT_2416";
const char *token = "SOvwzgVxqQBNJnKYeUFo4Ff0suI0YT9yFEFqD1aA";
const char *thing = "LED_Control";
AntoIO anto(user, token, thing);    /* initialize AntoIO instance */
void setup(){
  pinMode(D1,OUTPUT); 
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("Anto library version: ");
  Serial.println(anto.getVersion()); // lf;dmgfdlgdldgdgmfgmslkg;ls
  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");//dgagfsfgbfbxvbxvxbxv
  anto.begin(ssid, pass, messageReceived);
  Serial.println("\nConnected Anto done");
  anto.sub("LED1");              /*Subscript Channels "LED1"*/
}
void loop(){
  anto.mqtt.loop();
}
// a callback function for arriving data.
void messageReceived(String thing, String channel, String payload) {
    Serial.print("Recieved: ");
    Serial.print(thing);
    Serial.print("/");
    Serial.print(channel);
    Serial.print("-> ");
    Serial.println(payload);//fzgzgzgzgzgzgdzgz
    if(channel.equals("LED1"))
      digitalWrite(D1,(payload == "1")? 1:0);
}
