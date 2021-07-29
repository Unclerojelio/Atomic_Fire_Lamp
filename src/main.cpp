#include <Arduino.h>
#include <FastLED.h>
#include "../include/fire.h"

#define NUM_LEDS_PER_STRIP 52

// These pins are usually used for the OLED display. If we later want to use the OLED then
// move the data wires to 13,12,14,27 
#define ARM1 4           
#define ARM2 16
#define ARM3 17
#define ARM4 5

CRGB arm1Leds[NUM_LEDS_PER_STRIP];
CRGB arm2Leds[NUM_LEDS_PER_STRIP];
CRGB arm3Leds[NUM_LEDS_PER_STRIP];
CRGB arm4Leds[NUM_LEDS_PER_STRIP];

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
  
    uint16_t beatA = beatsin16(35, 0, 255);
    uint16_t beatB = beatsin16(30, 0, 255);
    uint16_t beatC = beatsin16(25, 0, 255);
    uint16_t beatD = beatsin16(20, 0, 255);

  /*
    uint16_t beatA = beat8(35);
    uint16_t beatB = beat8(30);
    uint16_t beatC = beat8(25);
    uint16_t beatD = beat8(20);
  */
    fill_rainbow(arm1Leds, NUM_LEDS_PER_STRIP, (beatA+beatB)/2, 8);
    fill_rainbow(arm2Leds, NUM_LEDS_PER_STRIP, (beatB+beatC)/2, 8);
    fill_rainbow(arm3Leds, NUM_LEDS_PER_STRIP, (beatC+beatD)/2, 8);
    fill_rainbow(arm4Leds, NUM_LEDS_PER_STRIP, (beatD+beatA)/2, 8);
  

    //fire1.DrawFire();
    //fire2.DrawFire();
    //fire3.DrawFire();
    //fire4.DrawFire();
    FastLED.show();

    EVERY_N_SECONDS(1) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
    delay(33);
}