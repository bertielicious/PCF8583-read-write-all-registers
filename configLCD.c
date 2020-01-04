#include "config.h"
#include "pulse.h"
#include "nibToBin.h"
void configLCD(void)    // 4 bit mode for Hitachi HD44780U LCD 
{
   __delay_ms(100);     // step 1
   
   nibToBin(LOW, 0x03); //step 2
   __delay_ms(5);
   
   nibToBin(LOW, 0x03); //step 3
   __delay_ms(1);
   
   nibToBin(LOW, 0x03); //step 4
   __delay_ms(1);
   
   nibToBin(LOW, 0x02); //step 5
   __delay_ms(1);
   
   nibToBin(LOW, 0x02); //step 6a
   __delay_ms(1);
   
  nibToBin(LOW, 0x08);// nibToBin(LOW, 0x08); //step 6b
   __delay_ms(1);
   
   nibToBin(LOW, 0x00); //step 7a
   __delay_ms(1);
   
   nibToBin(LOW, 0x08); //step 7b
   __delay_ms(1);
   
   nibToBin(LOW, 0x00); //step 8a
   __delay_ms(5);
   
   nibToBin(LOW, 0x01); //step 8b
   __delay_ms(5);
   
   nibToBin(LOW, 0x00); //step 9a
   __delay_ms(1);
   
   nibToBin(LOW, 0x06); //step 9b
   __delay_ms(1);
   
   nibToBin(LOW, 0x00); //step 11a
   __delay_ms(1);
   
   nibToBin(LOW, 0x0c); //step 11b
   __delay_ms(1);
}
