#include"config.h"
#include "dateInput.h"
#include "byteToBin.h"
#include "PCF8583Write.h"
#include <stdio.h>
#include "clearRow.h"
void setupDate(void)
{
    uchar Lsbm, Msbm, Lsbd, Msbd, yrLsb, yrMsb = 0;
    uchar result, dayResult;
    
    
    switch(state)   // start at state = 9
    {
        case 10:
            if(UP == 1)
            {
                
                state = 10;
            }
            else if(UP == 0)
            { 
                state = 11;
            }
            break;
            
        case 11:
            if(UP == 0 && month < 12)
            {
                month++;
                __delay_ms(250);
                state = 11;
            }
            else if(DOWN == 0)
            {
                state = 12;
            }
            else if(UP==1 && ENT==0)
            {
                state = 13;
            }
            break;
            
        case 12:
            if(DOWN == 0 && month >0)
            {
                month--;
                __delay_ms(250);
                state = 12;
            }
            else if(UP==0 && month <12)
            {
                state = 11;
            }
            else if(DOWN == 1 && ENT == 0)
            {
                state = 13;
            }
            break;
            
        case 13:
            result = decToBcd(month);    
          printf("month in SM %d\n", result) ;   
            PCF8583Write(0xa0,0x06,result & 0x3f);// write month
            state = 14;
            break;
            
        case 14:
            if(UP == 1)
            {
                state = 14;
            }
            else if(UP==0)
            {
                state = 15;
            }
            break;
            
        case 15:
            if(UP ==0 && day < 31)
            {
                day++;
                __delay_ms(250);
                state = 15;
            }
            else if(DOWN == 0 && day > 0)
            {
                state = 16;
            }
            else if(UP==1 && ENT==0)
            {
                state = 17;
            }
            break;
            
        case 16:
            if(DOWN ==0 && day >0)
            {
                day--;
                __delay_ms(250);
                state = 16;
            }
            else if(UP==0)
            {
                state = 15;
            }
            else if(DOWN ==1 && ENT ==0)
            {
                state = 17;
            }
            
            break;
            
        case 17:
            result = decToBcd(day);    
            dayResult = result & 0x3f;
          printf("day in SM %d\n", result) ;   
            PCF8583Write(0xa0,0x05,result & 0x3f);// write day
            state = 18;
            break;
            
        case 18:
            if(UP==1)
            {
                state = 18;
            }
            else if (UP==0)
            {
                state = 19;
            }
            break;
            
        case 19:
            if(UP==0)
            {
                year++;
                __delay_ms(250);
                state = 19;
            }
            else if(DOWN==0)
            {
                state = 20;
            }
            else if(UP==1 && ENT==0)
            {
                state = 21;
            }
            break;
            
        case 20:
            if(DOWN==0 && year >0)
            {
                year--;
                __delay_ms(250);
                state = 20;
            }
            else if(UP==0)
            {
                state = 19;
            }
            else if(DOWN==1 && ENT==0)
            {
                state = 21;
            }
            break;
            
        case 21:
            yrLsb = year%10;
            yrMsb = year/10;
        
            byteToBin(0,0x88);
            byteToBin(1, yrMsb + 0x30);
            byteToBin(1, yrLsb + 0x30);
            
            
            
            clearRow(0xc0, 0xd3);
            clearRow(0x94, 0xa7);
            clearRow(0xd4, 0xe7);
            state = 22;
            break;
            
        case 22:
            break;
            
        
    }  
    if(state <22)
    {
        Lsbm = month%10;            // display month data on RHS of LCD
        Msbm = month/10;
        byteToBin(0, 0xd1);
        byteToBin(1, Msbm + 0x30);
        byteToBin(1, Lsbm + 0x30);
        
        Lsbd = day%10;              // display day data
        Msbd = day/10;
        byteToBin(0, 0xa5);
        byteToBin(1, Msbd + 0x30);
        byteToBin(1, Lsbd + 0x30);
        
        yrLsb = year%10;              // display year data
        yrMsb = year/10;
        byteToBin(0, 0xe5);
        byteToBin(1, yrMsb + 0x30);
        byteToBin(1, yrLsb + 0x30);
    
    }
}
