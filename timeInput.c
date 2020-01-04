#include "config.h"
#include "byteToBin.h"
void timeInput(void)
{
    uchar time[] = {"enter time"};
    uchar hrs[6] = {"hours"};
    uchar minz[] = {"minutes"};
    uchar *ptr;
    
    ptr= &time[0];
    byteToBin(0,0x80);  // 1st line position
    while( *ptr > 0)
    {
      byteToBin(1, *ptr);
      ptr++;
    }
    ptr = &minz[0];
    byteToBin(0,0xd4);  // 4th line position 0
    while( *ptr > 0)
       {
        byteToBin(1, *ptr);
        ptr++;
       }
            
    ptr = &hrs[0];
    byteToBin(0,0x94);  // 3rd line position 0
    while( *ptr > 0)
      {
        byteToBin(1, *ptr);
        ptr++;
      }
}
