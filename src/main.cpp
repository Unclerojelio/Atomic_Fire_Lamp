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


#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include "fire.h"
#include "lamp.h"
#include "rainbow.h"
#include "solid.h"
#include "secrets.h"


ClassicFireEffect fire1(arm1Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
ClassicFireEffect fire2(arm2Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
ClassicFireEffect fire3(arm3Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
ClassicFireEffect fire4(arm4Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero

void setup() {

  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  WiFi.mode(WIFI_STA); //Optional
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

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
