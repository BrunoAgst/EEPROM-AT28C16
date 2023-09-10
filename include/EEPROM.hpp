#ifndef EEPROM
#define EEPROM

#include "Arduino.h"

class eeprom {
    public:
        eeprom(const int CLK, const int LATCH, const int DS_DATA, const int OE, const int WE, const int IO0, const int IO1, const int IO2, const int IO3, const int IO4, const int IO5, const int IO6, const int IO7);
        void setAddress(int8_t hex);
        void configureControlPins(void);
        void configureEEPROMRead(void);
        void configureEEPROMWrite(void);
        void readEEPROM(int8_t address);
        void writeEEPROM(int8_t address, byte data);
        
    private:
        int _CLK;
        int _LATCH;
        int _DS_DATA;
        int _OE;
        int _WE;
        int _IO0;
        int _IO1;
        int _IO2;
        int _IO3;
        int _IO4;
        int _IO5;
        int _IO6;
        int _IO7;
};

#endif