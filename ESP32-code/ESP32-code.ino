#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

// Import the credentials file
#include "secret.h"

// Set the pins for I2C bmp280 sensor
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

#define LEDpin 2 

// Set the variables for the time client
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec =3600;

// Create bmp, wifi and mqtt objects
Adafruit_BMP280 bmp;
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(115200);
  pinMode(LEDpin,OUTPUT);
  digitalWrite(LEDpin,LOW);

  // Connect to the WiFi network
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\nConnected to Wi-Fi');

  // Setting up temp sensor
  unsigned status;
  status = bmp.begin(0x76);
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  // Configure time server
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // set the CA
  wifiClient.setCACert(local_root_ca);

  // Configure mqtt client
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(onMsgRes);

  // Connect to the mqtt server
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)) {
      Serial.println("Connected to MQTT broker");
      mqttClient.publish("chat/message",  "BOT-1023603 joined the chat");
      mqttClient.subscribe("chat/message");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  mqttClient.loop();
}

// Function that will handle bot commands.
void onMsgRes(char* topic, byte* data, unsigned int len) {
  String message;

  for (int i = 0; i < len; i++) {
    message += (char)data[i];
  }
  Serial.println(message);
  if(message == "BOT-1023603: temp"){
    String messageToSend = String("BOT-1023603: temp=") + String(bmp.readTemperature() + String(" C"));
    char charBuf[50];
    messageToSend.toCharArray(charBuf, 50);
    mqttClient.publish("chat/message",  charBuf);
  }
  if(message == "BOT-1023603: led:aan"){
    digitalWrite(LEDpin, HIGH);
    mqttClient.publish("chat/message",  "BOT-1023603: led is aangezet");
  }
  if(message == "BOT-1023603: led:uit"){
    digitalWrite(LEDpin, LOW);
    mqttClient.publish("chat/message",  "BOT-1023603: led is uitgezet");
  }
}