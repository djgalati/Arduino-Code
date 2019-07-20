
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

char ssid[] = "sidewalkslamher";
char pass[] = "Oddrabbit629";
bool power=false;
int NUM_LEDS = 10;
IPAddress piip(192, 168, 0, 2);
//IPAddress myip(192, 168, 0, 41);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, D2, NEO_RGBW + NEO_KHZ800);
WiFiServer server(80);

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  Serial.begin(9600);   
  
  //LED Pins
  pinMode(D6, OUTPUT);
  strip.begin();
  strip.show();
  strip.setBrightness(150);
  colorWipe(strip.Color(255, 255, 255, 255));

  // Connect to WiFi network
  delay(100);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid,pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    colorWipe(strip.Color(0, 0, 255, 0));
    delay(500);
    Serial.print(".");
    colorWipe(strip.Color(255, 255, 255, 255));
  }
  Serial.println("Successfully connected");
  colorWipe(strip.Color(0, 255, 0, 0));
  printCurrentNet();
  printWiFiData();

  // Start the server
  server.begin();
  Serial.println("Server started");
  colorWipe(strip.Color(0, 0, 0, 0));
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request (GET /StripOn HTTP/1.1)
  
  //IF statement will splice request
  if(req.indexOf("GET /0 HTTP/1.1") != -1){
    colorWipe(strip.Color(0, 0, 0, 0));
    power=false;
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + power + "\r");
  }
  if(req.indexOf("GET /1 HTTP/1.1") != -1){
    colorWipe(strip.Color(255, 255, 255, 255));
    power=true;
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + power + "\r");
  }
  if(req.indexOf("GET /S HTTP/1.1") != -1){
    client.flush();
    // This will send the response to the client
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + power + "\r");
    Serial.println(String("HTTP/1.1 200 OK")+"\n\n" + power + "\r"); 
  }
 
  delay(10);
  Serial.println("Client disonnected");
}



//SUB-FUNCTIONS

void printWiFiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP address : ");
  Serial.println(ip);
  Serial.println("");
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

// print the SSID of the network you're attached to:
void printCurrentNet() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI): ");
  Serial.println(rssi);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void RGBLoop(){
  for(int j = 0; j < 3; j++ ) { 
    // Fade IN
    for(int k = 0; k < 256; k++) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}


void pulseWhite(uint8_t wait) {
  for(int j=0; j<256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }

  for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }
}



void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
