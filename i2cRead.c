#include "config.h"
uchar i2cRead(void)
{
    uchar buf = 0;
    SSPCON2bits.RCEN = 1;       // receive the data byte from the PCF8583 slave
    while(!SSPSTATbits.BF);     //wait for all 8 bits to be received
    buf = SSPBUF;               // save received data in buf 
    SSPCON2bits.ACKDT = 1;      // prepare to send NACK
    SSPCON2bits.ACKEN = 1;      // initiate NACK
    while(ACKEN);               // wait for NACK to repeat
    return buf;
}
