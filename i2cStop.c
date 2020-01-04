#include "config.h"
void i2cStop(void)
{
    SSPCON2bits.PEN = 1;        // initiate Stop condition on SDA and SCL pins. Auto cleared in hardware
    while(PEN); // wait for Stop condition to complete
}
