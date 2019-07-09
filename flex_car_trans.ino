#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

int msg[2];
RF24 radio(5,10);
const uint64_t pipe = 0xE7E8F0F0E1LL;

void setup() {
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}

void loop() {
  msg[0]=analogRead(A0);
  msg[1]=analogRead(A1);
  radio.write(&msg[0], sizeof(msg));
  radio.write(&msg[1], sizeof(msg));
  Serial.println(msg[0]);
  Serial.println(msg[1]);
}
