#include "config.h"
void configUsart(void)
{
    CM1CON0 = 0x00;         // comparators off
    CM2CON0 = 0x00;
    TRISBbits.TRISB7 = 0;   // TX pin is an output
    TXSTAbits.TXEN = 1;     // enable transmitter. TXIF is now set
    TXSTAbits.SYNC = 0;     // configure for asynchronous operation
    RCSTAbits.SPEN = 1;     // enables EUSART and configures TX pin as output
    SPBRG = 0x19;           // baud set to 2400
}
