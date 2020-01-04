/*
 * File:   main.c
 * Author: Phil Glazzard
 *
 * Created on 19 November 2019, 18:49
 */
/* Software Construction
 1. Problem definition
 * Control of a motorised door to the chicken coup where the door will be:
 a)  Open if the light level is daylight or the clock timer has been 
 * triggered to open the door, or if the manual open button has been pressed.
 b) Closed if the light level is night level or the clock timer has been 
 * triggered to close the door or the manual close button has been 
 * pressed
 2. Display on LCD the date, time, door open time, door close time, timer ON/OFF
 * light sensor ON/ OFF, manual OPEN/ CLOSE ON/ OFF and battery charge level on 
 * an LCD with three button keypad to control all of above. Confirm key presses
 *  via buzzer.
 3. Via blu-tooth connection, transmit all LCD display info to phone app, and 
 * also allow control of all door functions from the app.
 4. Microcontroller to be in sleep mode except when:
 * a) door needs to move from closed to open or open to closed due to timer or 
 * light sensor inputs or manual close/ open button.
 * b) someone presses a keypad button (time out back to sleep mode after 
 * 2 minutes without button activity)
 * (c) blue tooth transmit and receive
 2. Sub systems
 * a) LCD
 * b) uC sleep
 * c) blue tooth
 * d) door
 * e) timer/ clock
 * f) light sensor
 * g) keypad
 * h) solar psu
 * i) motor
 * 
 3. Structs
 * a) LCD
 *  date(day, month, year)
 *  time (hour, minutes, seconds)
 *  door (open time, close time)
 *  timer(on, off)
 *  set time(door open time, door close time)
 *  light sensor (on, off)
 *  light sensor (adjust up time, adjust down time)
 *  manual door button (open, close)
 *  battery charge level display (o% - 100%)
 *  keypad with three buttons (up, down, enter)
 *  confirm key press with buzzer (key pressed, key not pressed)
 * 
 * b) uC sleep
 * if (blue tooth active or button pressed or door needs to open or close (light sensor or timer))
 *    wake up
 *    run required code
 *    else
 *    sleep
 * 
 * c) blu-tooth
 *    transmit
 *    receive
 *    run necessary code
 * 
 * d) door
 *    open 
 *    close
 *    open or close door
 * 
 * e) clock/ timer
 *      check open
 *      check close
 *      open or close door
 * 
 * f) light sensor
 *      check light
 *      check dark
 *      open or close door
 * 
 * g) keypad
 *    check button press
 *       which button pressed
 *       setup screen or exit to main loop
 *       take action or open / close door
 *  
 * 
 * h) solar psu
 *      charge LiPo battery
 *      display battery charge level
 * 
 * i) motor
 *    motor moves clockwise = open door
 *    motor moves anti-clockwise = close door
 * 
 * 
 *                  16f1459
 *                  ---------
 *   +5 Volts    1 |Vdd      | 20 0 Volts
        LCD D6   2 |RA5   RA0| 19   - PUSH BUTTON
 *    motor ACW  3 |RA4   RA1| 18   + PUSH BUTTON
       MCLR      4 |RA3      | 17  MOTOR DIRECTION
 *  ENT PBUTTON  5 |RC5   RC0| 16  BOTTOM LIMIT SWITCH
 *    RS         6 |RC4   RC1| 15  motor CW
 *    EN         7 |RC3   RC2| 14  TOP LIMIT SWITCH
 *    LCD D4     8 |RC6   RB4| 13  SDA
 *    LCD D5     9 |RC7   RB5| 12  LCD D7
 *    TX        10 |RB7   RB6| 11  SCL
 *                  ---------
 *
 */

#include "config.h"
#include "configOsc.h"
#include "configPorts.h"
#include "configUsart.h"
#include "putch.h"
#include <stdio.h>
#include "configLCD.h"
#include "pulse.h"
#include "nibToBin.h"
#include "byteToBin.h"
#include "configI2c.h"
#include "i2cStart.h"
#include "i2cWrite.h"
#include "i2cRestart.h"
#include "PCF8583Read.h"
#include "PCF8583Write.h"
#include "setupTime.h"
#include "dateInput.h"
#include "timeInput.h"
#include "clearRow.h"
#include "setupDate.h"
#include "decToHex.h"
#include "hexToDec.h"

void main()
{
    configOsc();        // configure internal clock to run at 16MHz
    configPorts();      // configure PORTS A/ B/ C
    configUsart();      // allow serial comms to PC for debugging
    configLCD();        // 20 x 4 LCD set up for 4 bit operation
    configI2c();        // I2C setup with PCF8583 RTC chip
    printf("hello!\n"); // test serial port
    
    /* define variables for seconds, minutes, hours, date, month and year*/
    uchar secondsSet = 0;
    uchar seconds, resultSecs, readSecs;
    uchar secMsb, secLsb, numSec = 0;
    uchar minMsb, minLsb = 0;
    uchar minutes, minutesSet, resultMins, readMins;
    uchar hours, hoursSet, resultHours, readHours;
    uchar hrsLsb, hrsMsb = 0;
    uchar date, dateSet, resultDate, readDate;
    uchar dateLsb, dateMsb = 0;
    uchar month, monthSet, resultMonth, readMonth;
    uchar monthLsb, monthMsb = 0;
    uchar wkday, wkdaySet, resultWkday, readWkday;
    uchar yr ,yrSet, resultYr, readYr = 0;
    uchar yrLsb, yrMsb = 0;
    /*Initialise time and date*/
    secondsSet = 30;
    minutesSet = 8;
    hoursSet = 12;
    dateSet = 4;
    wkdaySet = 5;
    monthSet = 1;
    yrSet = 0;
    
    /*write time and date to PCF8583*/
    PCF8583Write(0xa0, CTRLSTAT, 0x80);         //turn counting off until counter settings loaded
    
    seconds = decToHex(secondsSet);            // convert secs from decimal to BCD
    PCF8583Write(0xa0, SECS, seconds);
    
    minutes = decToHex(minutesSet);
    PCF8583Write(0xa0, MINS, minutes);
    
    hours = decToHex(hoursSet);
    PCF8583Write(0xa0, HRS, hours);
    
    date = decToHex(dateSet);
    PCF8583Write(0xa0, YRDATE, date);
    
    month = decToHex(monthSet);
    PCF8583Write(0xa0, DAYMTHS, month);
    
    PCF8583Write(0xa0, CTRLSTAT, 0x00);         //turn counting ON until counter settings loaded
    
    
    
    while(1)
    {
        /* read time and date from PCF8583*/
        resultSecs = PCF8583Read(0xa0,SECS);
        readSecs = hexToDec(resultSecs);       // convert secs from BCD to decimal
        printf("secs %d\t", readSecs);
         
        resultMins = PCF8583Read(0xa0,MINS);
        readMins = hexToDec(resultMins);
        printf("mins %d\t", readMins);
        
        resultHours = PCF8583Read(0xa0,HRS);
        readHours = hexToDec(resultHours);
        printf("hours %d\t", readHours);
        
        resultDate = PCF8583Read(0xa0, YRDATE);
        readDate =  hexToDec(resultDate & 0x3f);
        printf("date %d\t", readDate);
        
        resultMonth = PCF8583Read(0xa0, DAYMTHS);
        readMonth = hexToDec(resultMonth & 0x1f);
        printf("month %d\t", readMonth);
        
        resultYr = PCF8583Read(0xa0, YRDATE);
        readYr = hexToDec((resultYr & 0xc0)>>6);
        printf("year %d\n", readYr);
        
        /*write time and date to LCD*/
        
        secLsb = readSecs%10;       // write secs on LCD
        secMsb = readSecs/10;
        byteToBin(0,0x92);
        byteToBin(1, secMsb + 0x30);
        byteToBin(1, secLsb + 0x30);
        
        byteToBin(0,0x91);
        byteToBin(1, 0x3a);
         
        minLsb = readMins%10;       // write mins on LCD
        minMsb = readMins/10;
        byteToBin(0,0x8f);
        byteToBin(1, minMsb + 0x30);
        byteToBin(1, minLsb + 0x30);
        
        byteToBin(0,0x8e);          // colon
        byteToBin(1, 0x3a);
        
        hrsLsb = readHours%10;       // write hours on LCD
        hrsMsb = readHours/10;
        byteToBin(0,0x8c);
        byteToBin(1, hrsMsb + 0x30);
        byteToBin(1, hrsLsb + 0x30);
        
        dateLsb = readDate%10;       // write date on LCD
        dateMsb = readDate/10;
        byteToBin(0,0x80);
        byteToBin(1, dateMsb + 0x30);
        byteToBin(1, dateLsb + 0x30);
        
        byteToBin(0,0x82);              // fwd slash
        byteToBin(1, 0x2f);
        
        monthLsb = readMonth%10;       // write month on LCD
        monthMsb = readMonth/10;
        byteToBin(0,0x83);              
        byteToBin(1, monthMsb + 0x30);
        byteToBin(1, monthLsb + 0x30);
        
         byteToBin(0,0x85);              // fwd slash
        byteToBin(1, 0x2f);
        
        monthLsb = readYr%10;       // write month on LCD
        monthMsb = 20/10;
        byteToBin(0,0x86);              
        byteToBin(1, monthMsb + 0x30);
        byteToBin(1, monthLsb + 0x30);
        
        
         __delay_ms(980);
        
    }
}