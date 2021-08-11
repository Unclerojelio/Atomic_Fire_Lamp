//+--------------------------------------------------------------------------
//
// Atomic Fire Lamp - (c) 2021 Roger Banks.  All Rights Reserved.
//
// File:        lamp.h
//
// Description:
//
//   Declarations for Atomic Fire Lamp.
//
//---------------------------------------------------------------------------

#pragma once
#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

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