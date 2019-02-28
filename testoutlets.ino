/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */
int R1=1;
void setup() {
  // prepare GPIO2
  pinMode(D2, OUTPUT);
  digitalWrite(D2, R1);     //EVERY RELAY WILL TURN OFF IN THE BEGGINING
}
int i=0;
void loop() {
  if(i>=1000){
    digitalWrite(D2, R1);
    R1=!R1;
    i=0;
    
  }
  i++;
  delay(1);
}
  

