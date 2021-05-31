# FiberOptic_Neopixel_GRBW
Arduino / ESP32 code for FiberOptic LED Lamp using GRBW LED strip

See: https://www.instructables.com/Fiber-Optic-LED-Lamp

I adapted the code to suit my GRBW addressable LED strips. The FastLED library does not support these GRBW strips, but Neopixel does. But the original code for the 'Noise effect' as sugested is only available for FastLED. See: https://www.instructables.com/Fiber-Optic-and-LEDs-a-Wall-Decoration
So I initialize both libraries, and let FastLED do the work, then in the final stage I copy the FastLED values to the Neopixel strip and add the bri(brightness) value to the white LED.
