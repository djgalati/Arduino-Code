#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

  int R1=1;
  int R2=1;
  int R3=1;
  int R4=1;
const char* ssid = "suddenlink.net-AE72";
const char* password = "ripedude";
IPAddress piip(192, 168, 0, 85);
IPAddress myip(192, 168, 0, 125);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(2, D6, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(2, D7, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(1, D8, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(1, D9, NEO_RGBW + NEO_KHZ800);
WiFiServer server(80);

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  
  Serial.begin(115200);
  
  //Relay Pins
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);

  //LED Pins
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);

  //Since the relays need to be grounded to turn on, setting all outputs to high will disable all outlets
  digitalWrite(D2, 1);
  digitalWrite(D3, 1);
  digitalWrite(D4, 1);
  digitalWrite(D5, 1);

  strip1.begin();
  strip1.show();
  strip1.setBrightness(100);
  strip2.begin();
  strip2.show(); 
  strip2.setBrightness(100);
  strip3.begin();
  strip3.show();
  strip3.setBrightness(100);
  strip4.begin();
  strip4.show(); 
  strip4.setBrightness(100);
  colorWipe1(strip1.Color(255, 255, 255, 255));
  colorWipe2(strip2.Color(255, 255, 255, 255));
  colorWipe3(strip3.Color(255, 255, 255, 255));
  colorWipe4(strip4.Color(255, 255, 255, 255));
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  //Sets Status LED's on outlets
  if(!R1){
    rainbow1();
  }
  else if(R1){
    colorWipe1(strip1.Color(0, 0, 0)); // off
  }
  if(!R2){
    rainbow2();
  }
  else if(R2){
    colorWipe2(strip2.Color(0, 0, 0)); // off
  }
  if(!R3){
    rainbow3();
  }
  else if(R3){
     colorWipe3(strip3.Color(0, 0, 0)); // off
  }
  if(!R4){
    rainbow4();
  }
  else if(R4){
     colorWipe4(strip4.Color(0, 0, 0)); // off
  }
  
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
  
  // Match the request (GET /R1/S HTTP/1.1)
  

  //RELAY-OUTLET 1
  if(req.indexOf("GET /R1/0 HTTP/1.1") != -1){
    R1 = 1;
    digitalWrite(D2, R1);
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + 0 + "\r");
  }
  if(req.indexOf("GET /R1/1 HTTP/1.1") != -1){
    R1 = 0;
    digitalWrite(D2, R1);
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + 1 + "\r");
  }
  if(req.indexOf("GET /R1/S HTTP/1.1") != -1){
    client.flush();
    // This will send the response to the client
    if(R1){
      client.print(String("HTTP/1.1 200 OK")+"\n\n" + 0 + "\r");
      colorWipe1(strip1.Color(0, 255, 0));
      delay(100);
    }
    else if(!R1){
      client.print(String("HTTP/1.1 200 OK")+"\n\n" + 1 + "\r");
      colorWipe1(strip1.Color(255, 0, 0));
      delay(100);
    }
    Serial.println(String("HTTP/1.1 200 OK")+"\n\n" + !R1 + "\r"); 
  }

  //RELAY-OUTLET 2
   if(req.indexOf("GET /R2/0 HTTP/1.1") != -1){
    R2 = 1;
    digitalWrite(D3, R2);
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + 0 + "\r");
  }
  if(req.indexOf("GET /R2/1 HTTP/1.1") != -1){
    R2 = 0;
    digitalWrite(D3, R2);
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + 1 + "\r");
  }
  if(req.indexOf("GET /R2/S HTTP/1.1") != -1){
    client.flush();
    // This will send the response to the client
    if(R2){
      client.print(String("HTTP/1.1 200 OK")+"\n\n" + 0 + "\r");
      colorWipe2(strip2.Color(0, 255, 0));
      delay(100);
    }
    else if(!R2){
      client.print(String("HTTP/1.1 200 OK")+"\n\n" + 1 + "\r");
      colorWipe2(strip2.Color(255, 0, 0));
      delay(100);
    }
    Serial.println(String("HTTP/1.1 200 OK")+"\n\n" + !R2 + "\r"); 
  }

  if(req.indexOf("GET /R3/0 HTTP/1.1") != -1){
    R3 = 1;
    digitalWrite(D4, R3);
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + 0 + "\r");
  }
  if(req.indexOf("GET /R3/1 HTTP/1.1") != -1){
    R3 = 0;
    digitalWrite(D4, R3);
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + 1 + "\r");
  }
  if(req.indexOf("GET /R3/S HTTP/1.1") != -1){
    client.flush();
    // This will send the response to the client
    if(R3){
      client.print(String("HTTP/1.1 200 OK")+"\n\n" + 0 + "\r");
      colorWipe3(strip3.Color(0, 255, 0));
      delay(100);
    }
    else if(!R3){
      client.print(String("HTTP/1.1 200 OK")+"\n\n" + 1 + "\r");
      colorWipe3(strip3.Color(255, 0, 0));
      delay(100);
    }
    Serial.println(String("HTTP/1.1 200 OK")+"\n\n" + !R3 + "\r"); 
  }
  
   if(req.indexOf("GET /R4/0 HTTP/1.1") != -1){
    R4 = 1;
    digitalWrite(D5, R4);
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + 0 + "\r");
  }
  if(req.indexOf("GET /R4/1 HTTP/1.1") != -1){
    R4 = 0;
    digitalWrite(D5, R4);
    client.print(String("HTTP/1.1 200 OK")+"\n\n" + 1 + "\r");
  }
  if(req.indexOf("GET /R4/S HTTP/1.1") != -1){
    client.flush();
    // This will send the response to the client
    if(R4){
      client.print(String("HTTP/1.1 200 OK")+"\n\n" + 0 + "\r");
      colorWipe4(strip4.Color(0, 255, 0));
      delay(100);
    }
    else if(!R4){
      client.print(String("HTTP/1.1 200 OK")+"\n\n" + 1 + "\r");
      colorWipe4(strip4.Color(255, 0, 0));
      delay(100);
    }
    Serial.println(String("HTTP/1.1 200 OK")+"\n\n" + !R4 + "\r"); 
  }

  delay(10);
  Serial.println("Client disonnected");
}


// Fill the dots one after the other with a color
void colorWipe1(uint32_t c) {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, c);
    strip1.show();
  }
}

void colorWipe2(uint32_t c) {
  for(uint16_t i=0; i<strip2.numPixels(); i++) {
    strip2.setPixelColor(i, c);
    strip2.show();
  }
}

void colorWipe3(uint32_t c) {
  for(uint16_t i=0; i<strip3.numPixels(); i++) {
    strip3.setPixelColor(i, c);
    strip3.show();
  }
}

void colorWipe4(uint32_t c) {
  for(uint16_t i=0; i<strip4.numPixels(); i++) {
    strip4.setPixelColor(i, c);
    strip4.show();
  }
}

void rainbow1() {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel1((i+j) & 255));
    }
    strip1.show();
  }
}

void rainbow2() {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip2.numPixels(); i++) {
      strip2.setPixelColor(i, Wheel2((i+j) & 255));
    }
    strip2.show();
    delay(5);
  }
}

void rainbow3() {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip3.numPixels(); i++) {
      strip3.setPixelColor(i, Wheel1((i+j) & 255));
    }
    strip3.show();
    delay(5);
  }
}

void rainbow4() {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip4.numPixels(); i++) {
      strip4.setPixelColor(i, Wheel2((i+j) & 255));
    }
    strip4.show();
    delay(5);
  }
}

uint32_t Wheel1(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint32_t Wheel2(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip2.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip2.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip2.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}
uint32_t Wheel3(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip3.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip3.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip3.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint32_t Wheel4(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip4.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip4.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip4.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}
