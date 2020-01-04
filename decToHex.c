#include "config.h"
uchar decToHex(uchar dec)
{
    return (((dec/10)<<4)|(dec%10));
}
