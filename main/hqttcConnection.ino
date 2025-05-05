#include <WiFiClientSecure.h>
#include <ArduinoMqttClient.h>

#include "secrets.h"

//Grabs data from secrets.h
char ssid[] = _SSID;
char pass[] = _PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);


const char broker[] = "io.adafruit.com";
int        port     = 1883;

const long interval = 3000;
unsigned long previousMillis = 0;

float count = 0.0;

void InitalizeHQTTCConnection() {
  
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for native USB port only
  //}
  delay(1000);

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  mqttClient.setId(_ClientID);

  // You can provide a username and password for authentication
  mqttClient.setUsernamePassword(_Username, _Token);

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  //waits untill it is connected to broker
  while (!mqttClient.connect(broker, port)) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  digitalWrite(14, HIGH);  
  delay(500);
  digitalWrite(14, LOW);

  //mqttClient.subscribe(_Commands);
  mqttClient.subscribe(_Start);

  delay(250);

  mqttClient.beginMessage(_ToServer);
  mqttClient.print("(C) Connected To Client");
  mqttClient.endMessage();

  waitForOnFromServer();

}

void waitForOnFromServer() {
  // avoids being disconnected by the broker
  while (true)
  {
    mqttClient.poll();

    unsigned long currentMillis = millis();
    
    //Don't overthrotal
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      mqttClient.beginMessage(_ToServer);
      mqttClient.print("(W) Waiting for message to start");
      mqttClient.endMessage();
    }

    int messageSize = mqttClient.parseMessage();

    //Amount of bytes that the "ON" Message is
    if (messageSize == 2) {
      Serial.print("Starting Robot");
      mqttClient.beginMessage(_ToServer);
      mqttClient.print("(S) Starting Robot");
      mqttClient.endMessage();
      return;
    }
  }
}