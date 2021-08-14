//+--------------------------------------------------------------------------
//
// Atomic Fire Lamp - (c) 2021 Roger Banks.  All Rights Reserved.
//
// File:        solid.h
//
// Description:
//
//   Draws solid color to arms of lamp retrofitted with WS2812b 
//   RGB LED strips.
//
//---------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "lamp.h"

void DrawSolid(CRGB color) {
  fill_solid(arm1Leds, NUM_LEDS_PER_STRIP, color);
  fill_solid(arm2Leds, NUM_LEDS_PER_STRIP, color);
  fill_solid(arm3Leds, NUM_LEDS_PER_STRIP, color);
  fill_solid(arm4Leds, NUM_LEDS_PER_STRIP, color);
}