/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

#define MR 0
#define MB 1
#define MG 2

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:v
  Serial.begin(9600);
  pinMode(MR, OUTPUT);
  pinMode(MB, OUTPUT);
  pinMode(MG, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(A5);
  Serial.println(sensorValue);//must read from -23C to 66C but reads from -25C to 105C... .684 per divison difference
  delay(10);
  if(sensorValue<382){//from 0-342
    if(sensorValue>0){
      digitalWrite(MG, (sensorValue/1.5));
    }
  }
  else if(sensorValue<700){//from 342-683
     if(sensorValue>325){
      digitalWrite(MB, (sensorValue-302)/1.5);
    }
  }
  else if(sensorValue<1024){//from 683-1024
    if(sensorValue>663){
      digitalWrite(MR, (sensorValue-684)/1.5);
    }
  }
}
