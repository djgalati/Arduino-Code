#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define RL D7 //Rear Left Upper Light Unit : 8 LED's
#define RR D6  //Rear Right Upper Light Unit : 8 LED's
#define FL D5  //Front Left Lower Light Unit : 3 LED's
#define FR D4  //Front Right Lower Light Unit : 3 LED's
#define LM D3  //Front Middle Lower Light Unit : 2 LED's

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel S = Adafruit_NeoPixel(8, RL, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel T = Adafruit_NeoPixel(8, RR, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel R = Adafruit_NeoPixel(3, FL, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel I = Adafruit_NeoPixel(3, FR, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel P = Adafruit_NeoPixel(2, LM, NEO_GRB + NEO_KHZ800);

// IMPORTANT HARDWARE SETUP INFO: 
// ==============================
// To reduce NeoPixel burnout risk:
//          - add 1000 uF capacitor across pixel power leads, 
//          - add 300 - 500 Ohm resistor on first pixel's data input,
//          - and minimize distance between Arduino and first pixel.  
//          - Avoid connecting on a live circuit...if you must, connect GND first.

void setup() {
  
  S.begin();
  T.begin();
  R.begin();
  I.begin();
  P.begin();
  
  // Initialize all pixels to 'off'
  S.show(); 
  T.show();
  R.show();
  I.show();
  P.show();

  // DO NOT EXCEED 234 WHEN POWERING ALL LIGHTS VIA A 5V1A CIRCUIT
  S.setBrightness(75);
  T.setBrightness(75);
  R.setBrightness(75);
  I.setBrightness(75);
  P.setBrightness(75);
}

void loop() {
  colorWipe(S.Color(100,48,53), 1);
  colorWipe(T.Color(100,48,53), 1);
  colorWipe(R.Color(100,48,53), 1);
  colorWipe(I.Color(100,48,53), 1);
  colorWipe(P.Color(100,48,53), 1);
  delay(1);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<S.numPixels(); i++) {
    S.setPixelColor(i, c);
    S.show();
  }
  for(uint16_t i=0; i<T.numPixels(); i++) {
    T.setPixelColor(i, c);
    T.show();
  }
  for(uint16_t i=0; i<R.numPixels(); i++) {
    R.setPixelColor(i, c);
    R.show();
  }
  for(uint16_t i=0; i<I.numPixels(); i++) {
    I.setPixelColor(i, c);
    I.show();
  }
  for(uint16_t i=0; i<P.numPixels(); i++) {
    P.setPixelColor(i, c);
    P.show();
  }
  delay(wait);
}
