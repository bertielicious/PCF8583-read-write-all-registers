#include "config.h"
void i2cRestart(void)
{
    SSPCON2bits.RSEN = 1; //initiate re-start condition  
    while(RSEN);     // wait for repeated start to complete
    PIR1bits.SSP1IF = 0;  // clear interrupt flag
}
