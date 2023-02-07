#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* mqtt_server = "your_MQTT_SERVER_IP_ADDRESS";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT server");
    } else {
      Serial.println("Failed to connect to MQTT server, trying again in 5 seconds");
      delay(5000);
    }
  }
  client.loop();
}
