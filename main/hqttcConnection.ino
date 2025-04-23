#include <WiFiClientSecure.h>
#include <ArduinoMqttClient.h>

#include "secrets.h"
#include "config.h"

//Grabs data from secrets.h
char ssid[] = _SSID;
char pass[] = _PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);


const char broker[] = "io.adafruit.com";
int        port     = 1883;

const long interval = 15000;
unsigned long previousMillis = 0;

float count = 0.0;

void InitalizeConnection() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  mqttClient.setId(_ClientID);

  // You can provide a username and password for authentication
  mqttClient.setUsernamePassword(_Username, _Token);

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  while (!mqttClient.connect(broker, port)) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  mqttClient.subscribe(_Commands);
  mqttClient.subscribe(_Start);

  sequenceConnect();
}

//Don't use
void sendMotors(float LM, float RM) {
  mqttClient.beginMessage(_LMotor);
  mqttClient.print(LM);
  mqttClient.endMessage();

  mqttClient.beginMessage(_RMotor);
  mqttClient.print(RM);
  mqttClient.endMessage();
}

//Don't use
void sendSensors(float LS, float CS, float RS) {
  mqttClient.beginMessage(_LSensor);
  mqttClient.print(LS);
  mqttClient.endMessage();

  mqttClient.beginMessage(_CSensor);
  mqttClient.print(CS);
  mqttClient.endMessage();

  mqttClient.beginMessage(_RSensor);
  mqttClient.print(RS);
  mqttClient.endMessage();
}

void sequenceConnect() {
  // avoids being disconnected by the broker
  while (true)
  {
    //Serial.println(".");
    mqttClient.poll();

    //unsigned long currentMillis = millis();
    
    //Don't overthrotal
    //if (currentMillis - previousMillis >= interval) {
    //  previousMillis = currentMillis;

    //  Serial.print("Sending message");
      //sendMotors(count, count);
      //sendSensors(count, count, count);

    //  Serial.println();

    //  count++;
    //}

    int messageSize = mqttClient.parseMessage();
    if (messageSize) {
      // we received a message, print out the topic and contents
      Serial.print("Received a message with topic '");
      Serial.print(mqttClient.messageTopic());
      Serial.print("', length ");
      Serial.print(messageSize);
      Serial.println(" bytes:");
      mqttClient.beginMessage(_Commands);
      mqttClient.print("ON!");
      mqttClient.endMessage();
      return;
    }
  }
}