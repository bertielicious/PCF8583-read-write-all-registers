#include "config.h"
void pulse(void)
{
    EN = HIGH;
    __delay_ms(1);
    EN = LOW;
}
