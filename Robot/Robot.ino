#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

String msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  //Odbiornik
   Serial.begin(9600);
   radio.begin();
   radio.openReadingPipe(1,pipe);
   radio.startListening();
  //Prawe koło do przodu
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  //Prawe koło do tyłu
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  
  //LEWE KOŁO DO TYŁU
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  
  //LEWE KOŁO DO PRZODU
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

}

void left()
  {
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
  }
void right()
  {
    digitalWrite(5, LOW);
    digitalWrite(2, LOW);
  }
void forward()
  {
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
  }  
void reverse()
  {
    digitalWrite(5, LOW);
    digitalWrite(3, LOW);
  }
void stopEng()
  {
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
  }

void loop() {
  //odbiornik
  //digitalWrite(2, LOW);
   if (radio.available())
    {
      radio.read(msg, 64);
      //Serial.println(msg[0]);
      int x = msg[0].toInt();
      Serial.println(x);
      
        if(x == 1)
        {
          left();
        }
        else if(x == 2)
        {
          right();
        }
        else if(x == 3)
        {
          forward();
        }
        else if(x == 4)
        {
          reverse();
        }
        else if(x == 0 or x == 999)
        {
          stopEng();
        }
        else
        {
          stopEng();
        }
             
      }
          delay(20);
}
