//+--------------------------------------------------------------------------
//
// Atomic Fire Lamp - (c) 2021 Roger Banks.  All Rights Reserved.
//
// File:        main.cpp
//
// Description:
//
//   Atomic Fire Lamp is a lamp retrofitted with 4 WS2812b RGB LED strips.
//   This project controls those led strips with various animations and
//   effects.
//
//---------------------------------------------------------------------------

// https://www.upesy.com/blogs/tutorials/how-to-connect-wifi-acces-point-with-esp32
// https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/


#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "fire.h"
#include "lamp.h"
#include "rainbow.h"
#include "solid.h"
#include "secrets.h"

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS";

ClassicFireEffect fire1(arm1Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
ClassicFireEffect fire2(arm2Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
ClassicFireEffect fire3(arm3Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
ClassicFireEffect fire4(arm4Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      //digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      //digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {

  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  WiFi.mode(WIFI_STA); //Optional
  WiFi.begin(ssid, password);
  delay(2000);
  Serial.print("\nConnecting .");

  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());


  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ARM1, OUTPUT);
  pinMode(ARM2, OUTPUT);
  pinMode(ARM3, OUTPUT);
  pinMode(ARM4, OUTPUT);

  FastLED.addLeds<NEOPIXEL, ARM1>(arm1Leds, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, ARM2>(arm2Leds, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, ARM3>(arm3Leds, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, ARM4>(arm4Leds, NUM_LEDS_PER_STRIP);

  FastLED.setBrightness(50);
  FastLED.clear(true);

  Serial.println("Waiting for connections...");
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  switch (1)
  {
  case 1:
    DrawRainbow();
    break;

  case 2:
    FastLED.clear();
    fire1.DrawFire();
    fire2.DrawFire();
    fire3.DrawFire();
    fire4.DrawFire();
    FastLED.delay(20);
    break;

  case 3:
    DrawSolid(CRGB::White);
    break;

  case 4:
    DrawSolid(CRGB::Black);
    break;

  case 5:
    DrawSolid(CRGB(255, 0, 0));
    break;
  }

  FastLED.show(50);

  EVERY_N_SECONDS(1) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
