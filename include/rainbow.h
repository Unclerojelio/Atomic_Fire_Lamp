//+--------------------------------------------------------------------------
//
// Atomic Fire Lamp - (c) 2021 Roger Banks.  All Rights Reserved.
//
// File:        rainbow.h
//
// Description:
//
//   Draws animated rainbow effects to arms of lamp retrofitted with WS2812b 
//   RGB LED strips.
//
//---------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "lamp.h"

void RainbowWobble() {
  uint16_t beatA = beatsin16(35, 0, 255);
  uint16_t beatB = beatsin16(30, 0, 255);
  uint16_t beatC = beatsin16(25, 0, 255);
  uint16_t beatD = beatsin16(20, 0, 255);

  fill_rainbow(arm1Leds, NUM_LEDS_PER_STRIP, (beatA+beatB)/2, 8);
  fill_rainbow(arm2Leds, NUM_LEDS_PER_STRIP, (beatB+beatC)/2, 8);
  fill_rainbow(arm3Leds, NUM_LEDS_PER_STRIP, (beatC+beatD)/2, 8);
  fill_rainbow(arm4Leds, NUM_LEDS_PER_STRIP, (beatD+beatA)/2, 8);
}

void RainbowCrawl(bool reverse=false) {
  uint16_t beatA = beat8(35);
  uint16_t beatB = beat8(30);
  uint16_t beatC = beat8(25);
  uint16_t beatD = beat8(20);
  
  if(reverse) {
    fill_rainbow(arm1Leds, NUM_LEDS_PER_STRIP, 255-beatA, 8);
    fill_rainbow(arm2Leds, NUM_LEDS_PER_STRIP, 255-beatB, 8);
    fill_rainbow(arm3Leds, NUM_LEDS_PER_STRIP, 255-beatC, 8);
    fill_rainbow(arm4Leds, NUM_LEDS_PER_STRIP, 255-beatD, 8);
  }
  else {
    fill_rainbow(arm1Leds, NUM_LEDS_PER_STRIP, beatA, 8);
    fill_rainbow(arm2Leds, NUM_LEDS_PER_STRIP, beatB, 8);
    fill_rainbow(arm3Leds, NUM_LEDS_PER_STRIP, beatC, 8);
    fill_rainbow(arm4Leds, NUM_LEDS_PER_STRIP, beatD, 8);
  }
}

void DrawRainbow() {
  static int counter = 0;

  EVERY_N_MINUTES(1) {
    counter++;
    if(counter>3) {
      counter = 0;
    }
  }

  if(counter == 0) {
    RainbowCrawl(false);
  }
  else if(counter == 1) {
    RainbowWobble();
  }
  else if(counter == 2) {
    RainbowCrawl(true);
  }
  else {
    RainbowWobble();
  }
}