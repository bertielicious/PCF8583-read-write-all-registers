/*
 *                  16f1459
 *                  ---------
 *   +5 Volts    1 |Vdd      | 20 0 Volts
        LCD D6   2 |RA5   RA0| 19
 *    motor ACW  3 |RA4   RA1| 18
 *    MCLR/ RST  4 |RA3      | 17  MOTOR DIRECTION
 *    GREEN LED  5 |RC5   RC0| 16  LIGHT SENSOR (analog)
 *    RS         6 |RC4   RC1| 15  RTC INPUT
 *    EN         7 |RC3   RC2| 14  TOP LIMIT SWITCH
 *    LCD D4     8 |RC6   RB4| 13  SDA i2C
 *    LCD D5     9 |RC7   RB5| 12  LCD D7
 *    TX        10 |RB7   RB6| 11  SCL i2C
 *                  ---------
 motor CW and BOTTOM LIMIT SWITCH need to be allocated  uC pin each
 */
#include "config.h"
void configPorts(void)
{
    ANSELA = 0x00;                  // disable all analogue inputs
    ANSELB = 0x00;
    ANSELC = 0x00;
    
    CM1CON0 = 0x00;                 // all COMPARATORS off
    CM2CON0 = 0x00;
    CM1CON1 = 0x00;
    CM2CON1 = 0x00;
    
    //ENT PUSH BUTTON
    TRISCbits.TRISC5 = HIGH;      // RC5 pin 5 
   
    
    //LCD PINS
   TRISCbits.TRISC4 = LOW;      // RS pin 6
   TRISCbits.TRISC3 = LOW;      // EN pin 7
   TRISCbits.TRISC6 = LOW;      // D4 pin 8
   TRISCbits.TRISC7 = LOW;      // D5 pin 9
   TRISAbits.TRISA5 = LOW;      // D6 pin 2
   TRISBbits.TRISB5 = LOW;      // D7 pin 12
   
   //i2C PINS
   
   TRISBbits.TRISB6 = HIGH;     // SCL (serial clock) pin 11 (Open drain)
   TRISBbits.TRISB4 = HIGH;     // SDA (serial data) pin 13 (Open drain)
   
}
