#include "config.h"
void configI2c(void)
{
    TRISBbits.TRISB4 = 1;    // SDA (RB4 pin 13) set as an input pin (tri-state))
    TRISBbits.TRISB6 = 1;    // SCL (RB6 pin 11) set as an input pin (tri-state))
    
    
    
    SSPCON1bits.SSP1M3 = 1;  //I2C Master mode, clock = FOSC / (4 * (SSPADD+1))(4)
    SSPCON1bits.SSP1M2 = 0;
    SSPCON1bits.SSP1M1 = 0;
    SSPCON1bits.SSP1M0 = 0;
    
    SSPADD = 0x09;          // Fosc = 4MHz, SCL = 100kHz  
    SSPCON1bits.SSPEN = 1;   //Serial Port ENable bit, configures serial port
                                // and configures SDA and SCL pins
}
