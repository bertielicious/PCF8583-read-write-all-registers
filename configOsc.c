#include "config.h"
void configOsc(void)
{
    OSCCONbits.IRCF3 = 1;   //IRFC<3:0> = 1111 (16MHz internal clock)
    OSCCONbits.IRCF2 = 1;   //IRFC<3:0> = 1110 (8MHz internal clock)
    OSCCONbits.IRCF1 = 1;   //IRFC<3:0> = 1101 (4MHz internal clock)
    OSCCONbits.IRCF0 = 1;   //IRFC<3:0> = 1100 (2MHz internal clock)
    
    OSCCONbits.SCS1 = 1;    // internal oscillator block selected
    OSCCONbits.SCS0 = 1;    // SCS0 state is 'don't care'
    
}
