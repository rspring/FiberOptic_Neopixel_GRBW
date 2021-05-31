// Fiber-Optic-LED-Lamp:
//
// See: https://www.instructables.com/Fiber-Optic-LED-Lamp
//
// I adapted the code to suit my GRBW addressable LED strips
// The FastLED library does not support these GRBW strips, but Neopixel does.
// But the original code for the 'Noise effect' as sugested is only available for FastLED.
// See: https://www.instructables.com/Fiber-Optic-and-LEDs-a-Wall-Decoration
//
// So I initialize both libraries, and let FastLED do the work, then in the final stage I copy
// the FastLED values to the Neopixel strip and add the bri(brightness) value to the white LED.
//

#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define NUM_LEDS 32 
#define PIN 15
#define NEO_PTYPE  NEO_GRBW  // f.e. SK6812
#define BRIGHTNESS  255 // set max brightness

// FastLED
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;
TBlendType    currentBlending;                                // NOBLEND or LINEARBLEND
uint8_t maxChanges = 24;                                      // Number of tweens between palettes.

// NeoPixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_PTYPE + NEO_KHZ800);

void setup()
{
  Serial.begin(115200);
  delay(1000);
  strip.begin();
  strip.setBrightness(BRIGHTNESS); // set brightness
  strip.show(); // Initialize all pixels to 'off'
}


// *** REPLACE FROM HERE ***
void loop() { 
  Noiseloop();
}


// *************************
// ** LEDEffect Functions **
// *************************

void Noiseloop(){
  for(int i = 0; i< 1000; i++) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);  // Blend towards the target palette
    noise16_3();
    showStrip();
    delay(50);
  }
  targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
}

// ***************************************
// ** FastLed/NeoPixel Common Functions **
// ***************************************

// Apply LED color changes
void showStrip() {
 // NeoPixel
 strip.show();
}

// Set a LED color (not yet visible)
void setPixel(int Pixel, byte red, byte green, byte blue) {
 // NeoPixel
 strip.setPixelColor(Pixel, strip.Color(red, green, blue));
}

// Set a LED color (not yet visible)
void setPixel4(int Pixel, byte red, byte green, byte blue, byte white) {
 // NeoPixel
 strip.setPixelColor(Pixel, strip.Color(red, green, blue, white));
}

// Set all LEDs to a given color and apply it (visible)
void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}

// Set all LEDs to a given color and apply it (visible)
void setAll4(byte red, byte green, byte blue, byte white) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel4(i, red, green, blue, white); 
  }
  showStrip();
}

void noise16_3() {                                            // no x/y shifting but scrolling along 
  uint8_t scale = 1000;                                       // the "zoom factor" for the noise
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    uint16_t shift_x = 4223;                                  // no movement along x and y
    uint16_t shift_y = 1234;
    uint32_t real_x = (i + shift_x) * scale;                  // calculate the coordinates within the noise field
    uint32_t real_y = (i + shift_y) * scale;                  // based on the precalculated positions
    uint32_t real_z = millis()*2;                             // increment z linear
    uint8_t noise = inoise16(real_x, real_y, real_z) >> 7;    // get the noise data and scale it down
    uint8_t index = sin8(noise*3);                            // map led color based on noise data
    uint8_t bri   = noise;
    leds[i] = ColorFromPalette(currentPalette, index, bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
    setPixel4(i, leds[i].r, leds[i].g, leds[i].b, bri/4);
  }
}
