/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/addisonsimon/Lab12Slave/src/Lab12Slave.ino"
void takeAction(uint8_t state);
void setup();
void loop();
#line 1 "/Users/addisonsimon/Lab12Slave/src/Lab12Slave.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
volatile bool CS = false;
void takeAction(uint8_t state) {
  if (state) {
    CS = true;
  }
}
void setup() {
  pinMode(D8,OUTPUT);
  pinMode(D5,INPUT);
  SPI1.begin(SPI_MODE_SLAVE,D6);
  SPI1.setClockSpeed(1,MHZ);
  SPI1.setBitOrder(MSBFIRST);
  SPI1.setDataMode(SPI_MODE0);
  SPI1.onSelect(takeAction);
  digitalWrite(D8, HIGH);
}
void loop() {
  if (CS == true) {
    char rx[1];
    char tx[1];
    CS = false;
    SPI1.transfer(tx,rx,1,NULL);
    if (rx[0] == '1') {
      digitalWrite(D8,HIGH);
    }
    if (rx[0] == '0') {
      digitalWrite(D8,LOW);
    }
    if (digitalRead(D5)) {
      digitalWrite(D8,HIGH);
    }
    else {
      digitalWrite(D8,LOW);
    }
    if (rx[0] == '?') {
      tx[0] = digitalRead(D5);
      SPI1.transfer(tx,rx,1,NULL);
    }
  }
}