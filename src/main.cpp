#include <Arduino.h>

// MultipleStripsInOneArray - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up four NEOPIXEL strips on three
// different pins, each strip will be referring to a different part of the single led array

#include <FastLED.h>

#define NUM_STRIPS 4
#define NUM_LEDS_PER_STRIP 52
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  // tell FastLED there's 60 NEOPIXEL leds on pin D1, starting at index 0 in the led array
  FastLED.addLeds<NEOPIXEL, D1>(leds, 0, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin D2, starting at index 60 in the led array
  FastLED.addLeds<NEOPIXEL, D2>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin D3, starting at index 120 in the led array
  FastLED.addLeds<NEOPIXEL, D3>(leds, 2 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);

    // tell FastLED there's 60 NEOPIXEL leds on pin D4, starting at index 120 in the led array
  FastLED.addLeds<NEOPIXEL, D4>(leds, 3 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);

}

void loop() {
  for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    leds[i] = CRGB::Red;
    leds[i +     NUM_LEDS_PER_STRIP] = CRGB::Red;
    leds[i + 2 * NUM_LEDS_PER_STRIP] = CRGB::Red;
    leds[i + 3 * NUM_LEDS_PER_STRIP] = CRGB::Red;
    FastLED.show();
    leds[i] = CRGB::Black;
    leds[i +     NUM_LEDS_PER_STRIP] = CRGB::Black;
    leds[i + 2 * NUM_LEDS_PER_STRIP] = CRGB::Black;
    leds[i + 3 * NUM_LEDS_PER_STRIP] = CRGB::Black;
    delay(50);
  }
}