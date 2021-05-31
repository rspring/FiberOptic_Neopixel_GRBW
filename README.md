# FiberOptic_Neopixel_GRBW
Arduino / ESP32 code for FiberOptic LED Lamp using GRBW LED strip

See: https://www.instructables.com/Fiber-Optic-LED-Lamp
See: https://www.instructables.com/Fiber-Optic-and-LEDs-a-Wall-Decoration

I adapted the code to suit my GRBW addressable LED strips.
1) The FastLED library does not support these GRBW strips, but Neopixel does.
2) But the original code for the 'Noise effect' as sugested is only available for FastLED.

So I now use both libraries, and let FastLED do the work, then in the final stage I copy the FastLED RGB values to the Neopixel strip and assign the dimmed bri(brightness) value (divided by 4) to the white LED.

The result is a more pastel tint color used in the visualization of the 'Noise Effect' loop.
