//#include <Arduino_ESP32_OTA.h>

//#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include <WiFiClientSecure.h>

#include "secrets.h"
/*
#include <Arduino_ESP32_OTA.h>

#include <WiFi.h>
#include <ArduinoMqttClient.h>
//#include <AdafruitIO_ESP8266.h>
//#include <Arduino_ESP32_OTA.h>

#include "secrets.h"
*/

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

bool waitingForConection = true;

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

  //Assign the function to recive the messages
  mqttClient.onMessage(onMqttMessage);

  //mqttClient.subscribe(_Commands);
  mqttClient.subscribe(_Start);
  mqttClient.subscribe(_Commands);
  mqttClient.subscribe(_TurnDirection);
  mqttClient.subscribe(_Instructions);

  delay(250);

  mqttClient.beginMessage(_ToServer);
  mqttClient.print("(C) Connected To Client");
  mqttClient.endMessage();

  if (_MQTTCStart)
    waitForOnFromServer();
}

//Stalls the program until it recives ON from the broker
void waitForOnFromServer() {
  while (waitingForConection)
  {
    //Keeps the client connected to the broker
    HQTTCPole();

    unsigned long currentMillis = millis();
    
    //Send messages periodicaly to not overthrawtle
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      //Send message to the broker
      mqttClient.beginMessage(_ToServer);
      mqttClient.print("(W) Waiting for message to start");
      mqttClient.endMessage();
    }
  }
}

//Called when a message is sent by the broker
void onMqttMessage(int messageSize)
{
  if (mqttClient.messageTopic() == "ChessPlayer/feeds/cetaiotrobot31415.instructions")
  {
    String inString = "";
    while (mqttClient.available()) {
      inString += ((char)mqttClient.read());
    }
    Serial.println(inString);
    SetMovement(inString);
  }


  if (mqttClient.messageTopic() == "ChessPlayer/feeds/cetaiotrobot31415.direction")
  {
    char inString = (char)mqttClient.read();
    if (inString == 'L')
      changeDirection(0);
    if (inString == 'R')
      changeDirection(1);
    if (_TurnOnRecive)
    {
      SetToTurn();
    }

  }

  if (mqttClient.messageTopic() == "ChessPlayer/feeds/cetaiotrobot31415.commands")
  {
    String inString = "";
    //Serial.print("Number: ");
    while (mqttClient.available()) {
      inString += ((char)mqttClient.read());
    }
    float inNum = inString.toFloat();
    if (!_ModAllSpeeds)
      SetCarnavalSpeed(inNum);
    else
    {
      float newSpeedsInForm[2] = {-inNum, -inNum};
      SetSpeedAdjustmentFactor(newSpeedsInForm);
    }

  }
  //Amount of bytes that the "ON" Message is
    if (_MQTTCStart && mqttClient.messageTopic() == "ChessPlayer/feeds/cetaiotrobot31415.start" && messageSize == 2) {
      Serial.print("Starting Robot");
      mqttClient.beginMessage(_ToServer);
      mqttClient.print("(S) Starting Robot");
      mqttClient.endMessage();
      waitingForConection = false;
      
      Serial.println((char)mqttClient.read());
      return;
    }
}

//Keeps the client connected to the broker
void HQTTCPole()
{
  mqttClient.poll();
}