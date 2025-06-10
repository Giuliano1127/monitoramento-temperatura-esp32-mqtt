#include <WiFi.h>
#include <PubSubClient.h>
#include <math.h>

const float BETA = 3950;  // Beta do termistor, igual ao seu
const int ntcPin = 34;    // ADC ESP32, substituindo A0

// WiFi e MQTT (igual seu projeto)
const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "iot/esp32/sensor/temperatura";

WiFiClient espClient;
PubSubClient client(espClient);

void conectarWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32Client123")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

float lerTemperatura() {
  int analogValue = analogRead(ntcPin);

  // Ajuste do cálculo para 12 bits ADC no ESP32
  float celsius = 1 / (log(1 / (4095.0 / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;

  return celsius;
}

void setup() {
  Serial.begin(115200);
  conectarWiFi();

  client.setServer(mqttServer, mqttPort);
  conectarMQTT();
}

void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }
  client.loop();

  float temperatura = lerTemperatura();

  char payload[50];
  snprintf(payload, sizeof(payload), "%.2f", temperatura);
  client.publish(mqttTopic, payload);

  Serial.print("Temperatura publicada: ");
  Serial.println(payload);

  delay(5000);
}
