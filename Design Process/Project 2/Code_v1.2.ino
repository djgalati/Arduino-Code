#define B0 2//MSB, Bit 0
#define B1 3
#define B2 4
#define B3 5
#define B4 6
#define B5 7
#define B6 8//LSB, Bit 6

int b0;
int b1;
int b2;
int b3;
int b4;
int b5;
int b6;
int AVolts;//the actual voltage arduino reads from the analog signal
int DVolts;//the voltage our ADC clculates from the analog signal
int DInput;
int AInput;
static int DVariance=0.078740157;
static int AVariance=0.009765625;
int count = 0;

void setup() {
  Serial.begin(9600);// initialize serial communication at 9600 bits per second
  //the next 7 lines of code set all the ADC output bits to inputs on the arduino
  pinMode(B0, INPUT);
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);
  pinMode(B5, INPUT);
  pinMode(B6, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  AInput = analogRead(A5);
  //if(analogRead(A5)>=AVolts){
    //AInput = analogRead(A5)*AVariance;}
  if((digitalRead(B0))!=1){ 
    b0 = digitalRead(B0);}
  if((digitalRead(B1))!=1){   
    b1 = digitalRead(B1);}
  if((digitalRead(B2))!=1){ 
    b2 = digitalRead(B2);}
  if((digitalRead(B3))!=1){ 
    b3 = digitalRead(B3);}
  if((digitalRead(B4))!=1){ 
    b4 = digitalRead(B4);}
  if((digitalRead(B5))!=1){ 
    b5 = digitalRead(B5);}
  if((digitalRead(B6))!=1){ 
    b6 = digitalRead(B6);}
  if(count<4){
    b0=0;
    b1=0;
    b2=0;
    b3=0;
    b4=0;
    b5=0;
    b6=0;
  }
  
  DInput=b0*64+b1*32+b2*16+b3*8+b4*4+b5*2+b6;
  DVolts=DInput*DVariance;
  AVolts=AInput*AVariance;
  if(count>1000){
    Serial.print(b0);
    Serial.print(b1);
    Serial.print(b2);
    Serial.print(b3);
    Serial.print(b4);
    Serial.print(b5);
    Serial.println(b6);
    Serial.print("The ADC reads ");
    Serial.print(DVolts);
    Serial.print(" volts:  ");
    Serial.println(DInput);
    Serial.print("The Arduino reads ");
    Serial.print(AInput);
    Serial.println(" volts");
    count=0;
  }
  count++;
  delay(1);
}
