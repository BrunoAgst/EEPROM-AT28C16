#include <Arduino.h>
#include "../lib/EEPROM.cpp"

const int CLK = 24;
const int LATCH = 22;
const int DS_DATA = 23;
const int OE = 2;
const int WE = 3;
const int IO0 = 4;
const int IO1 = 5;
const int IO2 = 6;
const int IO3 = 7; 
const int IO4 = 8;
const int IO5 = 10;
const int IO6 = 11;
const int IO7 = 12;

void setup() {
  Serial.begin(9600);

  eeprom Memory(CLK, LATCH, DS_DATA, OE, WE, IO0, IO1, IO2, IO3, IO4, IO5, IO6, IO7);
  
  Memory.configureControlPins();
  
  const int8_t address = 0x00;
  byte data = 0x0F;

  Memory.writeEEPROM(address, data);
  Memory.readEEPROM(address);
}

void loop() {}