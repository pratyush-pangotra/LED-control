/*
  Raspberry Pi Pico + WS2812B test sketch (Arduino IDE)
  Board package: arduino-pico (Earle Philhower)
  Library: Adafruit_NeoPixel

  Wiring:
    Pico GP2 --[330-470ohm resistor]--> Strip DATA-IN
    Strip 5V/GND powered from buck converter (NOT from Pico)
    Buck converter GND, strip GND, and Pico GND all tied together
*/

#include <Adafruit_NeoPixel.h>

#define DATA_PIN    2      // Pico GP2 - change if wired to a different pin
#define NUM_LEDS    37    // update to match your strip

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(500);

  strip.begin();
  strip.setBrightness(40);   // start low (0-255), raise once confirmed working
  strip.show();              // initialize all pixels to 'off'

  Serial.println("NeoPixel initialized on Pico. Starting test pattern.");
}

void loop() {
  // 1. Solid red
  fillAll(strip.Color(255, 0, 0));
  delay(1000);

  // 2. Solid green
  fillAll(strip.Color(0, 255, 0));
  delay(1000);

  // 3. Solid blue
  fillAll(strip.Color(0, 0, 255));
  delay(1000);

  // 4. Chase / single pixel walk - confirms addressing order
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(255, 255, 255));
    strip.show();
    delay(150);
  }

  // 5. Off, pause before repeating
  strip.clear();
  strip.show();
  delay(1000);
}

void fillAll(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

