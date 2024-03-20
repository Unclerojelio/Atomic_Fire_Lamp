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
// https://randomnerdtutorials.com/solved-reconnect-esp32-to-wifi/

// Configured in Ha with this message:
// mosquitto_pub -r -t "homeassistant/light/Atomic_Fire_Lamp/config" -m '{"name": "Atomic_Fire_Lamp", "command_topic": "homeassistant/light/Atomic_Fire_Lamp/set", "state_topic": "homeassistant/light/Atomic_Fire_Lamp/state", "unique_id": "blinky_toy_01", "device": {"identifiers": ["living_room01"], "name": "Living" }}'


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

int mode = 1;
int brightness = 50;
int red = 0;
int green = 0;
int blue = 0;

const char* mqtt_server = "mqtt-broker.local";

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
  if (String(topic) == "set/esp32-4022d8ee50a0/power") {
    Serial.print("Changing output to ");
    if(messageTemp == "ON"){
      Serial.println("On");
      client.publish("status/esp32-4022d8ee50a0/power", "ON");
      //mode = 1;
    }
    else if(messageTemp == "OFF"){
      Serial.println("Off");
      client.publish("status/esp32-4022d8ee50a0/power", "OFF");
      mode = 4;
    }
  }
  else if (String(topic) == "set/esp32-4022d8ee50a0/effect") {
    Serial.print("Changing output to ");
    if(messageTemp == "Rainbow") {
      Serial.println("Rainbow");
      client.publish("status/esp32-4022d8ee50a0/effect", "Rainbow");
      mode = 1;
    }
    else if(messageTemp == "Fire") {
      Serial.println("Fire");
      client.publish("status/esp32-4022d8ee50a0/effect", "Fire");
      mode = 2;
    }
    else if(messageTemp == "Solid") {
      Serial.println("Solid");
      client.publish("status/esp32-4022d8ee50a0/effect", "Solid");
      mode = 5;
    }
    else if(messageTemp == "White") {
      Serial.println("White");
      client.publish("status/esp32-4022d8ee50a0/effect", "White");
      mode = 3;
    }
  }
  else if (String(topic) == "set/esp32-4022d8ee50a0/brightness") {
    Serial.print("Changing brightness to ");
    Serial.println(messageTemp);
    client.publish("status/esp32-4022d8ee50a0/brightness", messageTemp.c_str());
    brightness = messageTemp.toInt();
  }
  else if (String(topic) == "set/esp32-4022d8ee50a0/rgb") {
    Serial.print("Changing color to ");
    Serial.println(messageTemp);
    client.publish("status/esp32-4022d8ee50a0/rgb", messageTemp.c_str());
    int i1 = messageTemp.indexOf(',');
    int i2 = messageTemp.indexOf(',', i1+1);
    String red_str = messageTemp.substring(0, i1);
    String green_str = messageTemp.substring(i1 + 1, i2);
    String blue_str = messageTemp.substring(i2 + 1);
    red = red_str.toInt();
    green = green_str.toInt();
    blue = blue_str.toInt();
    brightness = messageTemp.toInt();
  }
  else if (String(topic) == "homeassistant/status") {
    if(messageTemp == "online") {
      Serial.println("Home Assistant is online");
    }
    else if(messageTemp == "offline") {
      Serial.println("Home Assistant is offline");
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
      client.subscribe("set/esp32-4022d8ee50a0/power");
      client.subscribe("set/esp32-4022d8ee50a0/brightness");
      client.subscribe("set/esp32-4022d8ee50a0/rgb");
      client.subscribe("set/esp32-4022d8ee50a0/effect");
      client.subscribe("homeassistant/status");
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
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());


  client.setServer(mqtt_server, 1883);
  client.setBufferSize(1024);
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

  FastLED.setBrightness(brightness);
  FastLED.clear(true);

  Serial.println("Waiting for connections...");
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  switch (mode)
  {
  case 1:
    DrawRainbow();
    //client.publish("esp32/status", "Rainbow");
    break;

  case 2:
    FastLED.clear();
    fire1.DrawFire();
    fire2.DrawFire();
    fire3.DrawFire();
    fire4.DrawFire();
    FastLED.delay(20);
    //client.publish("esp32/status", "Fire");
    break;

  case 3:
    DrawSolid(CRGB::White);
    //client.publish("esp32/status", "White");
    break;

  case 4:
    DrawSolid(CRGB::Black);
    //client.publish("esp32/status", "Off");
    break;

  case 5:
    DrawSolid(CRGB(red, green, blue));
    break;
  }

  FastLED.show(brightness);

  EVERY_N_SECONDS(1) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
