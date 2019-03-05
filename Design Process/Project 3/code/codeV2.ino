#include <Servo.h>
#define IR A0
#define sw1 A3
#define sw2 A4
#define sw3 A5
#define pmtrue 13//all defines preset pin number and name for all LED's
#define M6  12//LSB for Minutes
#define M5  2
#define M4  3
#define M3  4
#define M2  5
#define M1  6//MSB for Minutes
#define H4  7//LSB for Hours
#define H3  8
#define H2  9
#define H1  10//MSB for Hours

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
int seconds=45;
int minutes=50;
int hours=12;
int Tminutes=0;
int Thours=0;
bool PMTrue=LOW;
Servo SecHand;

void setup() {
pinMode(IR, INPUT);
pinMode(sw1, INPUT);
pinMode(sw2, INPUT);
pinMode(sw3, INPUT);
pinMode(pmtrue, OUTPUT);//This line and the next 10 lines set the pins as outputs to power the LED's indiviually
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
pinMode(13, OUTPUT);
SecHand.attach(11);
Serial.begin(9600);
}

void loop() {
  Serial.println(seconds);
  Serial.println(minutes);
  Serial.println(hours);
  int choice=0; //setup knob, variable must be set up here for switch(case) statement
  int Ctemp1=analogRead(sw2);
  int Ctemp2=analogRead(sw3);
  Serial.println(analogRead(A0));
  Serial.println(analogRead(A5));
  Serial.println(analogRead(A4));
  Serial.println(analogRead(A3));
  //all the arithmatic divides out the output for the time
  Thours=hours;
  Tminutes=minutes;
  h4=Thours%2;
  Thours=Thours/2;
  h3=Thours%2;
  Thours=Thours/2;
  h2=Thours%2;
  Thours=Thours/2;
  h1=Thours%2;
  m6=Tminutes%2;
  Tminutes=Tminutes/2;
  m5=Tminutes%2;
  Tminutes=Tminutes/2;
  m4=Tminutes%2;
  Tminutes=Tminutes/2;
  m3=Tminutes%2;
  Tminutes=Tminutes/2;
  m2=Tminutes%2;
  Tminutes=Tminutes/2;
  m1=Tminutes%2;
  //choice = Ctemp2+(2*Ctemp1);// make sure these are in the proper order
  switch (choice){
   case 0:
   SecHand.write(10);//This number 95 is a total guess, we will have to vary this a little bit. 90 should be stopped.
     if(true){//must correct this so when the arm passes the IR, SET TO TRUE DUE TO INPUTS NOT WORKING

        
        if(seconds>=59){
          minutes=minutes+1;
          seconds=0;
          if(minutes>=59){
            minutes=0;
            hours=hours+1;
            if(hours>=12){
              minutes=0;
              hours=1;
              PMTrue=!PMTrue;
            }
            else if(hours<12) {
             //hours=hours+1;
             
           }
           else if(minutes<59){
            minutes=minutes+1;
           }     
         }
        else if(seconds<59){
          seconds=seconds+1;
        } 
        }
      }   
   //All the code for the rest of this case is to display the current time
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
   digitalWrite(13,PMTrue);
   }
   case 1:
   SecHand.write(0);
    if((analogRead(sw1))>100){
      do{
      }while((analogRead(sw1))>100);
      PMTrue=!PMTrue;
    }
   case 2:
   SecHand.write(0);
    if((analogRead(sw1))>100){
     do{
      }while((analogRead(sw1))>100);
      if(minutes>=59){
        minutes=0;
      }
      else{
        minutes=minutes+1;
      }
    }
   case 3:
   SecHand.write(0);
    if((analogRead(sw1))>100){
      do{
      }while((analogRead(sw1))>100);
      if(hours>=12){
        hours=1;
      }
      else{
        hours=hours+1;
      }
    }
  }
  delay(1);
  Serial.print(h4);
  Serial.print(h3);
  Serial.print(h2);
  Serial.print(h1);
  Serial.print(m6);
  Serial.print(m5);
  Serial.print(m4);
  Serial.print(m3);
  Serial.print(m2);
  Serial.print(m1);
  Serial.print(PMTrue);
  seconds=seconds+1;
  if(hours==12){
    if(minutes==0){
      digitalWrite(13, HIGH);
    }
  }
  else if(hours!=12) {
    if(minutes!=0){
      digitalWrite(13, LOW);
    }
  }
}




