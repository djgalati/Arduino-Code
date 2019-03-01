#define pminput  0
#define pmtrue 1//all defines preset pin number and name for all LED's
#define M6  2//LSB for Minutes
#define M5  3
#define M4  4
#define M3  5
#define M2  6
#define M1  7//MSB for Minutes
#define H4  8//LSB for Hours
#define H3  9
#define H2  10
#define H1  11//MSB for Hours

int h1=0;//This and the next 10 lines are for each of the LED's for if it's on or off
int h2=0;
int h3=0;
int h4=0;
int m1=0;
int m2=0;
int m3=0;
int m4=0;
int m5=0;
int m6=0;
bool PMTrue=false;
int minutes=0;//the decimal number of the currently shown minutes
int hours=0;//the decimal number of the currently shown hours


void setup() {
  pinMode(A1, INPUT);//This line and the next 2 lines set up the input of what time is being stored on the other arduino
  pinMode(A2, INPUT);
  pinMode(pminput, INPUT);
  pinMode(PMTrue, OUTPUT);//This line and the next 10 lines set the pins as outputs to power the LED's indiviually
  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(H3, OUTPUT);
  pinMode(H4, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(M5, OUTPUT);
  pinMode(M6, OUTPUT);
}

void loop() {
  hours=analogRead(A1);// this line and the next 2 lines will update the time stores on the other arduino everytime the code loops
  minutes=analogRead(A2);
  PMTrue=digitalRead(pminput);
  h1=hours%2;//This line and the next 3 lines take hours stored and 
  hours=hours/2;
  h2=h1%2;
  hours=hours/2;
  h3=h2%2;
  hours=hours/2;
  h4=h3%2;
  m1=minutes%2;
  minutes=minutes/2;
  m2=m1%2;
  minutes=minutes/2;
  m3=m2%2;
  minutes=minutes/2;
  m4=m3%2;
  minutes=minutes/2;
  m5=m4%2;
  minutes=minutes/2;
  m6=m5%2;
  digitalWrite(H1, h1);
  digitalWrite(H2, h2);
  digitalWrite(H3, h3);
  digitalWrite(H4, h4);
  digitalWrite(M1, m1);
  digitalWrite(M2, m2);
  digitalWrite(M3, m3);
  digitalWrite(M4, m4);
  digitalWrite(M5, m5);
  digitalWrite(M6, m6);
  digitalWrite(pmtrue,PMTrue);
}
