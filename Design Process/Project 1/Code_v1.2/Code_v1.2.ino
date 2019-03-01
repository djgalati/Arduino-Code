/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

#define MR 0 //Red LED pin
#define MB 1//Blue LED pin
#define MG 2//Green LED pin
int C;//Celsius variable
int F;//Fahrenheit variable
int runt=millis();//time keeping variable to output the temperature

void setup() {
  Serial.begin(9600);// initialize serial communication at 9600 bits per second
  //sets up all 3 LED pins as outputs
  pinMode(MR, OUTPUT);
  pinMode(MB, OUTPUT);
  pinMode(MG, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(A5);
  if(sensorValue<300){//from 0-300 divisions, the Blue LED will be active
    digitalWrite(MG, LOW);
    digitalWrite(MR, LOW);
    if(sensorValue<50){
      digitalWrite(MB, 42);
    }
    else if(sensorValue<100){
      digitalWrite(MB, 127);
    }
    else if(sensorValue<150){
      digitalWrite(MB, 255);
    }
    else if(sensorValue<200){
      digitalWrite(MB, 255);
    }
    else if(sensorValue<250){
      digitalWrite(MB, 127);
    }
    else if(sensorValue<300){
      digitalWrite(MB, 42);
    }
    else{
      digitalWrite(MB, LOW);
    }
  }
  else if(sensorValue<525){//from 225-525 divisions, the Green LED will be active
     digitalWrite(MB, LOW);
     digitalWrite(MR, LOW);
     if(sensorValue<275){
      digitalWrite(MG, 42);
    }
    else if(sensorValue<325){
      digitalWrite(MG, 127);
    }
    else if(sensorValue<375){
      digitalWrite(MG, 255);
    }
    else if(sensorValue<425){
      digitalWrite(MG, 255);
    }
    else if(sensorValue<475){
      digitalWrite(MG, 127);
    }
    else if(sensorValue<525){
      digitalWrite(MG, 42);
    }
    else{
      digitalWrite(MG, LOW);
    }
  }
  else if(sensorValue<754){//from 450-754 divisions, the Red LED will be active
    digitalWrite(MG, LOW);
    digitalWrite(MB, LOW);
    if(sensorValue<500){
      digitalWrite(MR, 42);
    }
    else if(sensorValue<550){
      digitalWrite(MR, 127);
    }
    else if(sensorValue<600){
      digitalWrite(MR, 255);
    }
    else if(sensorValue<650){
      digitalWrite(MR, 255);
    }
    else if(sensorValue<700){
      digitalWrite(MR, 127);
    }
    else if(sensorValue<754){
      digitalWrite(MR, 42);
    }
    else{
      digitalWrite(MR, LOW);
    }
  }
  delay(1);
  runt=runt-1;
  //if the runt variable drops below 0, the program will output the current temperature readings from the AD592
  if(runt<0){
  Serial.print("The temperature is ");
  if (sensorValue>74){
    C = sensorValue/10.36;
  }
  else if (sensorValue<74){
    C = -1*(sensorValue/3.18);
  }
  else{
    C=0;
  }
  Serial.print(C);
  Serial.print(" degrees Celsius and ");
  F=C*(9/5)+32;
  Serial.print(F);
  Serial.println(" degrees Fahrenheit");
  runt=500;
  }
}
