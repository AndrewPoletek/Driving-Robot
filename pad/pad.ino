#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

String msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  // put your setup code here, to run once:
  //Lewy Analog X : A3
  //Lewy Analog Y: A4
  //Prawy Analog X : A5
  //Prawy Analog Y: A6
  //PRZYCISKI: {{1:D3, 2:D4, 3:D6, 4:D5, UP:A1, LEFT:A0, RIGHT:D8, DOWN:D7, 10:A2}}
  pinMode(A6, INPUT);
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop() {
  radio.write(msg, 32);    
  digitalWrite(2, HIGH);
  pinMode(6, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  //msg[0] = digitalRead(6);
  //msg[0] = analogRead(A3);
  if(analogRead(A3) > 900)
  {
    //LEFT RIDE
    msg[0] = 1;
  }
  else if(analogRead(A3) < 10)
  {
    //RIGHT RIDE
    msg[0] = 2;
  }
  else if(digitalRead(6) < 1)
  {
    //FORWARD
    msg[0] = 3;
  }
  else if(digitalRead(3) < 1)
  {
    //REVERSE
    msg[0] = 4;
  }
  else
  {
    msg[0]=999;
  }
  //Serial.println(digitalRead(3));
  Serial.println(msg[0]);
  //msg[0] = "1";
  radio.write(msg, 64);
  delay(50);
}
