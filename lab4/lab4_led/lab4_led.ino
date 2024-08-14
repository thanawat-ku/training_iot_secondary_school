#include "WiFi.h"
#include <PubSubClient.h>

const char* mqtt_server = "mqtt-dashboard.com";
WiFiClient espClient;
PubSubClient client(espClient);
String ssid = "Akita_kuse";
String password = "kuse1234";
String device_id = "1234";
int ledPin = 5;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
  }
  Serial.println(WiFi.localIP());  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void callback(char* topic, byte* message, unsigned int length) {
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  String topic_device="KUSELed/"+device_id;
  if (String(topic) == topic_device) {
    Serial.print("Changing output to ");
    if(messageTemp == "ON"){
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "OFF"){
      digitalWrite(ledPin, LOW);
    }
  }
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String topic="KUSELed/"+device_id;
    char buf[50];
    if (client.connect(buf)) {
      Serial.println("connected");
      // Subscribe
      topic.toCharArray(buf,topic.length() + 1);
      client.subscribe(buf);
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
}
