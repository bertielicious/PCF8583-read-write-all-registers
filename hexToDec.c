#include "config.h"
uchar hexToDec(uchar hex)
{
    return((hex>>4)*10 + (hex & 0x0f));
}
