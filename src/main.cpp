#include <Arduino.h>

// MultipleStripsInOneArray - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up four NEOPIXEL strips on three
// different pins, each strip will be referring to a different part of the single led array

#include <FastLED.h>
#include "../include/fire.h"

#define NUM_LEDS_PER_STRIP 52
CRGB arm1Leds[NUM_LEDS_PER_STRIP];
CRGB arm2Leds[NUM_LEDS_PER_STRIP];
CRGB arm3Leds[NUM_LEDS_PER_STRIP];
CRGB arm4Leds[NUM_LEDS_PER_STRIP];

ClassicFireEffect fire(NUM_LEDS_PER_STRIP, 20, 100, 3, 4, true, false);     // Outwards from Zero


// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  // tell FastLED there's 60 NEOPIXEL leds on pin 10
  FastLED.addLeds<NEOPIXEL, 4>(arm1Leds, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin 11
  FastLED.addLeds<NEOPIXEL, 16>(arm2Leds, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin 12
  FastLED.addLeds<NEOPIXEL, 17>(arm3Leds, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin 12
  FastLED.addLeds<NEOPIXEL, 5>(arm4Leds, NUM_LEDS_PER_STRIP);

  FastLED.setBrightness(50);
  FastLED.clear(true);

  Serial.begin(57600);
}

void loop() {
  /*
    uint16_t beatA = beatsin16(35, 0, 255);
    uint16_t beatB = beatsin16(30, 0, 255);
    uint16_t beatC = beatsin16(25, 0, 255);
    uint16_t beatD = beatsin16(20, 0, 255);
  */

  /*
    uint16_t beatA = beat8(35);
    uint16_t beatB = beat8(30);
    uint16_t beatC = beat8(25);
    uint16_t beatD = beat8(20);

    fill_rainbow(arm1Leds, NUM_LEDS_PER_STRIP, (beatA+beatB)/2, 8);
    fill_rainbow(arm2Leds, NUM_LEDS_PER_STRIP, (beatB+beatC)/2, 8);
    fill_rainbow(arm3Leds, NUM_LEDS_PER_STRIP, (beatC+beatD)/2, 8);
    fill_rainbow(arm4Leds, NUM_LEDS_PER_STRIP, (beatD+beatA)/2, 8);
  */

    fire.DrawFire();
    FastLED.show();

    EVERY_N_SECONDS(1) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
    delay(33);
}