#include <Arduino.h>
#include <FastLED.h>
#include "fire.h"
#include "lamp.h"
#include "rainbow.h"

//ClassicFireEffect fire1(NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
//ClassicFireEffect fire2(NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
//ClassicFireEffect fire3(NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero
//ClassicFireEffect fire4(NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero

void setup() {

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

  Serial.begin(57600);
}

void loop() {

  //fire1.DrawFire();
  //fire2.DrawFire();
  //fire3.DrawFire();
  //fire4.DrawFire();
  DrawRainbow();
  FastLED.show();

  EVERY_N_SECONDS(1) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  FastLED.delay(33);
}