#include <Servo.h>
#define IR A0
#define sw1 0
#define sw2 1
#define sw3 2
#define pmoutput  4
int seconds=0;
int minutes=0;
int hours=0;
bool PMTrue=false;
static int steps=60;//tells motor it should take 60 steps to complete 1 revolution
Servo SecHand;

void setup() {
pinMode(IR, INPUT);
pinMode(sw1, INPUT);
pinMode(sw2, INPUT);
pinMode(sw3, INPUT);
pinMode(pmoutput, OUTPUT);
pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(11, OUTPUT);
SecHand.attach(11);
}

void loop() {
  int choice=0; //setup knob, variable must be set up here for switch(case) statement
  int Ctemp1=digitalRead(sw2);
  int Ctemp2=digitalRead(sw3);
  choice = Ctemp2+(2*Ctemp1);// make sure these are in the proper order
  switch (choice){
   case 0:
   SecHand.write(95);
     if((analogRead(A0))<255){//must correct this so when the arm passes the IR
       if(seconds>=59){
         if(minutes>=59){
           if(hours>=12){
             minutes=0;
             hours=1;
             PMTrue=!PMTrue;
           }
           else if(hours<12) {
             minutes=0;
             hours=hours+1;
           }
          else if(minutes<59){
           minutes=minutes+1;
          }
        else if(seconds<59){
          seconds=seconds+1;
        }
      else{}
      }
    else{}
    }
   else{}
   }
   case 1:
   SecHand.write(90);
    if((digitalRead(sw1))==1){
      do{
      }while((digitalRead(sw1))==1);
      PMTrue=!PMTrue;
    }
   case 2:
   SecHand.write(90);
    if((digitalRead(sw1))==1){
     do{
      }while((digitalRead(sw1))==1);
      if(minutes>=59){
        minutes=0;
      }
      else{
        minutes=minutes+1;
      }
    }
   case 3:
   SecHand.write(90);
    if((digitalRead(sw1))==1){
      do{
      }while((digitalRead(sw1))==1);
      if(hours>=12){
        hours=1;
      }
      else{
        hours=hours+1;
      }
    }
  }
  analogWrite(A1, hours);
  analogWrite(A2, minutes);
  digitalWrite(pmoutput, PMTrue);
}




