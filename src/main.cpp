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

//#define BLYNK_PRINT Serial
#define BLYNK_USE_DIRECT_CONNECT

#include <Arduino.h>
#include <FastLED.h>
#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include "fire.h"
#include "lamp.h"
#include "rainbow.h"
#include "solid.h"
#include "secrets.h"

char auth[] = BLYNK_AUTH;
uint8_t blynk_brightness = 255;
uint8_t blynk_animation = 1;

BLYNK_WRITE(V0)
{
  blynk_brightness = param.asInt(); // assigning incoming value from pin V1 to a variable
}

BLYNK_WRITE(V1)
{
  blynk_animation = param.asInt();
}

ClassicFireEffect fire1(arm1Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
ClassicFireEffect fire2(arm2Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
ClassicFireEffect fire3(arm3Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
ClassicFireEffect fire4(arm4Leds, NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero

void setup() {

  Serial.begin(57600);

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
  Blynk.setDeviceName("Atomic_Fire_Lamp");
  Blynk.begin(auth);
}

void loop() {

  switch (blynk_animation)
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
  }

  FastLED.show(blynk_brightness);

  Blynk.run();

  EVERY_N_SECONDS(1) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
