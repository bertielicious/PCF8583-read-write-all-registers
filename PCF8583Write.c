#include "config.h"
#include "i2cStart.h"
#include "i2cWrite.h"
#include "i2cRestart.h"
#include "i2cRead.h"
#include "i2cStop.h"
void PCF8583Write(uchar slaveAddr, uchar regAddr, uchar dataByte)
{
   i2cStart();      // initiate i2c start condition 
   i2cWrite(slaveAddr); //send PCF8583 address  R/W bit is cleared
   if(SSPCON2bits.ACKSTAT == 1)    // if ACK bit was not received
    {
        SSPCON2bits.PEN = 1;        // initiate Stop condition on SDA and SCL
        while(SSPCON2bits.PEN == 1);// wait for Stop condition to complete
        return;
    }
   i2cWrite(regAddr);   //send hours (oxo4) or mins (0x03) address 
   if(SSPCON2bits.ACKSTAT == 1)    // if ACK bit was not received
    {
        SSPCON2bits.PEN = 1;        // initiate Stop condition on SDA and SCL
        while(SSPCON2bits.PEN == 1);// wait for Stop condition to complete
        return;
    }
   i2cWrite(dataByte); // send the data to be stored eg hours or minutes data
   if(SSPCON2bits.ACKSTAT == 1)    // if ACK bit was not received
    {
        SSPCON2bits.PEN = 1;        // initiate Stop condition on SDA and SCL
        while(SSPCON2bits.PEN == 1);// wait for Stop condition to complete
        return;
    }
   i2cStop();
}
