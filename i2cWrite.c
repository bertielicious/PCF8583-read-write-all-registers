#include "config.h"
#include <stdio.h>
void i2cWrite(uchar byte)
{
    SSPBUF = byte;                  // send the byte on the SDA pin (slave address plus RW bit or data byte)
    while(!SSP1IF);                  // wait for ACK - SSP1IF set on 9th clock cycle
    
    PIR1bits.SSP1IF = 0;
    __delay_us(5);
    if(SSPCON2bits.ACKSTAT)    // ACK bit was not received
    {
        SSPCON2bits.PEN = 1;        // initiate Stop condition on SDA and SCL
        while(PEN);// wait for Stop condition to complete
        return;
    } 
    
}
