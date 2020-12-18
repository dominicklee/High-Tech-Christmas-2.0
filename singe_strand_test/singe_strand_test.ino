#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS_A 300  /* Number of pixels */
#define UNIVERSE_A 1      /* Universe to listen for */
#define CHANNEL_START_A 1 /* Channel to start listening at */
#define DATA_PIN_A 14      /* Pixel output - GPIO14 / nodeMCU D5 */

#define NUM_PIXELS_B 300  /* Number of pixels */
#define UNIVERSE_B 2      /* Universe to listen for */
#define CHANNEL_START_B 1 /* Channel to start listening at */
#define DATA_PIN_B 12      /* Pixel output - GPIO12 / nodeMCU D6 */

#define NUM_PIXELS_C 50  /* Number of pixels */
#define UNIVERSE_C 3      /* Universe to listen for */
#define CHANNEL_START_C 1 /* Channel to start listening at */
#define DATA_PIN_C 13      /* Pixel output - GPIO13 / nodeMCU D7 */

Adafruit_NeoPixel pixels_a = Adafruit_NeoPixel(NUM_PIXELS_A, DATA_PIN_A, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixels_b = Adafruit_NeoPixel(NUM_PIXELS_B, DATA_PIN_B, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixels_c = Adafruit_NeoPixel(NUM_PIXELS_C, DATA_PIN_C, NEO_RGB + NEO_KHZ800);

void setup() {
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);

  pixels_a.begin();
  pixels_a.setBrightness(30);
  pixels_a.show(); // Initialize all pixels to 'off'

}

void loop() {

  // Some example procedures showing how to display to the pixels:
  colorWipe(pixels_a.Color(255, 0, 0), 50); // Red
  colorWipe(pixels_a.Color(0, 255, 0), 50); // Green
  colorWipe(pixels_a.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  theaterChase(pixels_a.Color(127, 127, 127), 50); // White
  theaterChase(pixels_a.Color(127, 0, 0), 50); // Red
  theaterChase(pixels_a.Color(0, 0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels_a.numPixels(); i++) {
    pixels_a.setPixelColor(i, c);
    pixels_a.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels_a.numPixels(); i++) {
      pixels_a.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels_a.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels_a.numPixels(); i++) {
      pixels_a.setPixelColor(i, Wheel(((i * 256 / pixels_a.numPixels()) + j) & 255));
    }
    pixels_a.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels_a.numPixels(); i=i+3) {
        pixels_a.setPixelColor(i+q, c);    //turn every third pixel on
      }
      pixels_a.show();

      delay(wait);

      for (uint16_t i=0; i < pixels_a.numPixels(); i=i+3) {
        pixels_a.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels_a.numPixels(); i=i+3) {
        pixels_a.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixels_a.show();

      delay(wait);

      for (uint16_t i=0; i < pixels_a.numPixels(); i=i+3) {
        pixels_a.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels_a.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels_a.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels_a.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
