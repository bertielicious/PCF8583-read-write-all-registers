/*
 * File:   byteToBin.c
 * Author: Phil Glazzard
 *
 * Created on 20 November 2019, 12:06
 */
#include "config.h"
#include "pulse.h"

void byteToBin(bool R, uchar byte)
{
    RS = R;
    D7 = (byte& 0b10000000) >> 7;
    D6 = (byte & 0b01000000) >> 6;
    D5 = (byte & 0b00100000) >> 5;
    D4 = (byte & 0b00010000) >> 4;
    pulse();
    
    
    RS = R;
    D7 = (byte & 0b00001000) >> 3;
    D6 = (byte & 0b00000100) >> 2;
    D5 = (byte & 0b00000010) >> 1;
    D4 = (byte & 0b00000001) >> 0;
    pulse();   
}