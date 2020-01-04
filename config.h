/* 
 * File:   config.h
 * Author: Phil Glazzard
 *
 * Created on 19 November 2019, 18:40
 */

#ifndef CONFIG_H
#define	CONFIG_H

void config (void);


// PIC16F1459 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = CLKDIV6 // CPU System Clock Selection Bit (CPU system clock divided by 6)
#pragma config USBLSCLK = 48MHz // USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x     // PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = ENABLED  // PLL Enable Bit (3x or 4x PLL Enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include<stdbool.h>
#define _XTAL_FREQ 16000000
// DIAGNOSTIC LED
#define ENT PORTCbits.RC5       // ENT switch pin 5
#define DOWN PORTAbits.RA0     // - switch pin 19
#define UP PORTAbits.RA1      // + switch pin 18

//LCD pins redefined
#define RS PORTCbits.RC4 
#define EN PORTCbits.RC3 
#define D4 PORTCbits.RC6 
#define D5 PORTCbits.RC7 
#define D6 PORTAbits.RA5 
#define D7 PORTBbits.RB5 

//i2c pins redefined
#define SDA PORTBbits.RB4       // pin 13
#define SCL PORTBbits.RB6       // pin 11


//PCD8583 registers redefined
#define CTRLSTAT 0x00
#define SECS 0x02
#define MINS 0x03
#define HRS 0x04
#define YRDATE 0x05
#define DAYMTHS 0x06

typedef unsigned char uchar;
uchar year, day, hour, month = 0;
uchar min, On, state = 0;

enum {LOW, HIGH};

#endif	/* CONFIG_H */

