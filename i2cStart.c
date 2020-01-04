#include "config.h"
void i2cStart(void)
{
    SSPCON2bits.SEN = 1;             // initiate start condition
    while(SEN);                         // wait until SSPIF is LOW (start condition is complete)
    PIR1bits.SSP1IF = 0;              // clear SSPIF flag
}
