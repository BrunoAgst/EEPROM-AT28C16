#include "Arduino.h"
#include "../include/EEPROM.hpp"

eeprom::eeprom(const int CLK, const int LATCH, const int DS_DATA, const int OE, const int WE, const int IO0, const int IO1, const int IO2, const int IO3, const int IO4, const int IO5, const int IO6, const int IO7){
    _CLK = CLK;
    _LATCH = LATCH;
    _DS_DATA = DS_DATA;
    _OE = OE;
    _WE = WE;
    _IO0 = IO0;
    _IO1 = IO1;
    _IO2 = IO2;
    _IO3 = IO3;
    _IO4 = IO4;
    _IO5 = IO5;
    _IO6 = IO6;
    _IO7 = IO7;
}

void eeprom::writeEEPROM(int8_t address, byte data){
  int i = 0;
  
  setAddress(address);
  configureEEPROMWrite();
  digitalWrite(_OE, 1);
  
  for(int pin = _IO7; pin >= _IO0; pin--){
    digitalWrite(pin, (data & (1 << (7 - i))) ? 1 : 0);
    i++;
  }
  
  digitalWrite(_WE, 0);
  delayMicroseconds(1);
  digitalWrite(_WE, 1);
  delay(10);
}

void eeprom::readEEPROM(int8_t address){
  byte data = 0;

  setAddress(address);
  configureEEPROMRead();
  digitalWrite(_OE, 0);
  
  Serial.print("Binary: ");
  for(int pin = _IO7; pin > _IO0; pin--){
    Serial.print(digitalRead(pin));
    data = (data << 1) + digitalRead(pin);
  }
  
  Serial.println();
  Serial.print("Data: ");
  Serial.println(data);
}

void eeprom::configureControlPins(void){
  pinMode(_CLK, OUTPUT);
  pinMode(_LATCH, OUTPUT);
  pinMode(_DS_DATA, OUTPUT);
  pinMode(_OE, OUTPUT);
  digitalWrite(_WE, HIGH);
  pinMode(_WE, OUTPUT);

  digitalWrite(_CLK, 0);
  digitalWrite(_LATCH, 0);
}

void eeprom::configureEEPROMRead(void){
  pinMode(_IO0, INPUT);
  pinMode(_IO1, INPUT);
  pinMode(_IO3, INPUT);
  pinMode(_IO4, INPUT);
  pinMode(_IO5, INPUT);
  pinMode(_IO6, INPUT);
  pinMode(_IO7, INPUT);  
}

void eeprom::configureEEPROMWrite(void){
  pinMode(_IO0, OUTPUT);
  pinMode(_IO1, OUTPUT);
  pinMode(_IO3, OUTPUT);
  pinMode(_IO4, OUTPUT);
  pinMode(_IO5, OUTPUT);
  pinMode(_IO6, OUTPUT);
  pinMode(_IO7, OUTPUT);  
}


void eeprom::setAddress(int8_t hex){
  for(int i = 0; i < 8; i++){
    digitalWrite(_CLK, 0);
    digitalWrite(_DS_DATA, (hex & (1 << (7 - i))) ? 1 : 0);
    digitalWrite(_CLK, 1);
  }

  digitalWrite(_LATCH, 1);
  digitalWrite(_LATCH, 0);
}