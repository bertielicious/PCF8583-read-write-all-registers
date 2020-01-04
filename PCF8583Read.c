#include "config.h"
#include "i2cStart.h"
#include "i2cWrite.h"
#include "i2cRestart.h"
#include "i2cRead.h"
#include "i2cStop.h"
uchar PCF8583Read(uchar slaveAddr, uchar regAddr)
{
    uchar temp;
    i2cStart();
    i2cWrite(slaveAddr);  // send slave address and write bit = 0
    i2cWrite(regAddr);          // regAddr = 0x02 seconds
    i2cRestart();
    i2cWrite(slaveAddr + 1);  // send slave address and read bit = 1
    __delay_us(5);
    temp = i2cRead();
    i2cStop();
    return temp;
}
