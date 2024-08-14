#include "WiFi.h"
#include <PubSubClient.h>

const char* mqtt_server = "mqtt-dashboard.com";
WiFiClient espClient;
PubSubClient client(espClient);
String ssid = "Akita_kuse";
String password = "kuse1234";
String device_id = "1234";
int swPin = 26;
int old_value=HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(swPin, INPUT_PULLUP);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
  }
  Serial.println(WiFi.localIP());  
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String id="KUSELed-"+device_id;
    char buf[50];
    id.toCharArray(buf,id.length() + 1);
    if (client.connect(buf)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  int new_value=digitalRead(swPin);
  if(old_value!=new_value){
    String topic="KUSELed/"+device_id;
    String command;
    if(new_value==LOW){
      command="ON";
    }else{
      command="OFF";
    }
    char buf1[50],buf2[20];
    topic.toCharArray(buf1,topic.length() + 1);
    command.toCharArray(buf2,command.length() + 1);
    client.publish(buf1,buf2);
    old_value=new_value;
  }
}
