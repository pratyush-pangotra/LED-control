# ESP32 + WS2812B LED Strip (Buck Converter Powered)

Basic setup and test for driving an addressable LED strip from an ESP32,
powered via a 12V supply → 5V buck converter.

## Hardware

- ESP32 devkit
- WS2812B (or compatible) addressable LED strip — 3 pins: 5V, GND, DATA
- 12V power supply
- 12V → 5V buck converter
- 330–470Ω resistor (data line protection)
- 1000µF capacitor, rated ≥6.3V (optional, smooths inrush current)

## Wiring

```
12V Supply (+) ──────────► Buck Converter (IN+)
12V Supply (–) ──────────► Buck Converter (IN–)

Buck Converter (OUT+, 5V) ──────────► LED Strip 5V
Buck Converter (OUT–, GND) ─────┬───► LED Strip GND
                                  └───► ESP32 GND

ESP32 GPIO2 ──[330–470Ω resistor]──► LED Strip DATA-IN
```

Capacitor (if used): across strip's 5V and GND pins, right at the strip's input end.

**Common ground is required.** Buck converter GND, strip GND, and ESP32 GND
must all be tied together, or the data signal won't have a stable reference.

## Setup order

1. Power the buck converter from the 12V supply with nothing else connected.
   Measure the output with a multimeter and trim to exactly 5V.
2. Connect strip 5V/GND to the buck converter output. Leave DATA disconnected
   and power on briefly to confirm the strip doesn't overheat.
3. Tie ESP32 GND to buck converter GND.
4. Connect ESP32 GPIO2 → resistor → strip DATA-IN.
5. Power ESP32 separately (USB or its own 5V), upload the test sketch below,
   and test at low brightness first.

## Test sketch

See `led_strip_test.ino`. Uses the FastLED library.

- Install via Arduino IDE: **Sketch → Include Library → Manage Libraries → search "FastLED"**
- Update `NUM_LEDS` and `DATA_PIN` to match your strip and wiring.
- Sketch starts at low brightness (40/255) — raise it gradually once confirmed working.

## Troubleshooting

- **Nothing lights up:** check common ground first — this is the most common issue.
- **First LED wrong color / flickering:** add the 1000µF capacitor and/or the data-line resistor if not already in place.
- **Random resets / flickering strip:** power draw is likely exceeding what's feeding the ESP32 — confirm strip power comes only from the buck converter, not the ESP32.
- **Wrong colors overall:** try switching the color order in code (`GRB` vs `RGB`) — WS2812B is commonly `GRB`.
