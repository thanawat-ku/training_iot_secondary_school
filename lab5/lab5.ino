//หน้าเว็บ https://www.hivemq.com/demos/websocket-client/
#include <WiFi.h>
#include <MQTT.h>
#include "DHT.h"
#define DHTPIN 16     // Digital pin connected to the DHT sensor
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
const char ssid[] = "YOUR_SSID";
const char pass[] = "YOUR_PASSWORD";
const char mqtt_broker[] = "mqtt-dashboard.com";
const char mqtt_topic[] = "groupX/temp";
const char mqtt_client_id[] = "arduino_group_x"; // must change this string to a unique value
int MQTT_PORT = 1883;
WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\nconnecting...");
  while (!client.connect(mqtt_client_id)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
  client.subscribe(mqtt_topic);
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);
  connect();
  dht.begin();
}

void loop() {
  client.loop();
  if (!client.connected()) {
    connect();
  }
  // publish a message roughly every 10 seconds.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    float t = dht.readTemperature();
    client.publish(mqtt_topic, "Temp = " + String(t));
  }
}