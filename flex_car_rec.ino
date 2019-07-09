#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
RF24 radio(5,10);
const uint64_t pipe = 0xE7E8F0F0E1LL;
int msg[2];

int mr1=9;
int mr2=8;
int ml1=7;
int ml2=6;
void setup() {
  radio.begin();
  radio.openReadingPipe(0,pipe);
  radio.startListening();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  Serial.begin(9600);
  pinMode(mr1,OUTPUT);
  pinMode(mr2,OUTPUT);
  pinMode(ml1,OUTPUT);
  pinMode(ml2,OUTPUT);
  Serial.println("started");

}

void loop() {
  Serial.println("loop:");
  if(radio.available())
  {
    Serial.println("inside");
    bool done = false;
    while(!done)
    {
      radio.read(&msg[0],sizeof(msg));
      radio.read(&msg[1],sizeof(msg));
      if(msg[0]<400&&msg[1]<500)
      {Serial.println("stop");
       wait();
        }
      else if(msg[0]>450&&msg[1]>550)
      {Serial.println("forward");
       forward();
        }  
      else if(msg[0]>400&&msg[1]<500)
      {Serial.println("left");
       left();
        } 
      else if(msg[0]<400&&msg[1]>500)
      {Serial.println("right");
       right();
        }   
      }
    }

}

void forward()
{
  digitalWrite(mr1,HIGH);
  digitalWrite(mr2,LOW);
  digitalWrite(ml1,HIGH);
  digitalWrite(ml2,LOW);
} 

void wait()
{
  digitalWrite(mr1,LOW);
  digitalWrite(mr2,LOW);
  digitalWrite(ml1,LOW);
  digitalWrite(ml2,LOW);
  }

void right()
{
  digitalWrite(mr1,HIGH);
  digitalWrite(mr2,LOW);
  digitalWrite(ml1,LOW);
  digitalWrite(ml2,HIGH);
  }
void left()
{
  digitalWrite(mr1,LOW);
  digitalWrite(mr2,HIGH);
  digitalWrite(ml1,HIGH);
  digitalWrite(ml2,LOW);
  }
