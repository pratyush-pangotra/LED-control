/*
  Raspberry Pi Pico + WS2812B - smooth continuous rainbow animation
  Board package: arduino-pico (Earle Philhower)
  Library: Adafruit_NeoPixel

  Wiring:
    Pico GP2 --[330-470ohm resistor]--> Strip DATA-IN
    Strip 5V/GND powered from buck converter (NOT from Pico)
    Buck converter GND, strip GND, and Pico GND all tied together
*/

#include <Adafruit_NeoPixel.h>

#define DATA_PIN    2      // Pico GP2 - change if wired to a different pin
#define NUM_LEDS    37     // matches your cut strip length

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

uint16_t animOffset = 0;   // drives the moving rainbow, wraps at 65536

void setup() {
  strip.begin();
  strip.setBrightness(60);   // 0-255, raise/lower to taste
  strip.show();
}

void loop() {
  rainbowCycle();
  delay(15);   // lower = faster animation, higher = slower
}

// Smooth moving rainbow across the whole strip, continuous with no pauses
void rainbowCycle() {
  for (int i = 0; i < NUM_LEDS; i++) {
    uint16_t pixelHue = animOffset + (i * 65536L / NUM_LEDS);
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  strip.show();
  animOffset += 256;   // speed of color rotation, adjust to taste
}
