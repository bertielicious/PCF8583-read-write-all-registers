#include "config.h"
#include "clearRow.h"
#include "byteToBin.h"
void clearRow(uchar startCol, uchar endCol)
{
    uchar col;
    byteToBin(0, startCol);
   for (col = startCol; col <=endCol; col++)
   {
       byteToBin(1, 0x20);
       
   }
}
