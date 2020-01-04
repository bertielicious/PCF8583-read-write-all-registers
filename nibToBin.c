#include "config.h"
#include "pulse.h"
void nibToBin(bool R, uchar nib )// value of R is LOW for command mode, HIGH for data mode
{
    RS = R;
    D7 = (nib & 0b00001000) >> 3;
    D6 = (nib & 0b00000100) >> 2;
    D5 = (nib & 0b00000010) >> 1;
    D4 = (nib & 0b00000001) >> 0;
    pulse();   
}
