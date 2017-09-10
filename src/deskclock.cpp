
#include <Arduino.h>

/** \file
 * Solder:Time Desk Clock
 * SpikenzieLabs.com
 *
 * By: MARK DEMERS, May 2013
 * Updated: Trammell Hudson <hudson@trmm.net>, Feb 2014
 * VERSION 1.1
 *
 * Brief:
 * Sketch used in the Solder: Time Desk Clock Kit, more info and build
 * instructions at http://www.spikenzielabs.com/stdc
 *
 * Updated information at http://trmm.net/SolderTime_Desk_Clock
 *
 *  LEGAL:
 * This code is provided as is. No guaranties or warranties are given
 * in any form. It is your responsibilty to determine this codes
 * suitability for your application.
 *
 * Changes:
 * A. Modified LEDupdateTHREE() void used by ST:2 Watch to function
 * with the new circuits in the Solder:Time Desk Clock
 * B. Modified port dirctions on some pins to deal with new circuits.
 * C. Changed sleep mode into a "change back to display time" mode
 */

#include <Wire.h>
#include <EEPROM.h>

#include <TimerOne.h>

#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

// int  i  =0;
// int  i2  =0;
// int  vite = 2;
// uint8_t incro = 0;
// uint8_t column = 0;
uint8_t TEXT = 65;
// int nextcounter = 0;

int ROWBITINDEX = 0;
int scrollCounter =0;
int ScrollLoops = 3;
int scrollSpeed = 300;                                    // was 1200
int blinkCounter = 0;
boolean blinkFlag = false;
boolean blinkON = true;
boolean blinkHour = false;
boolean blinkMin = false;
#define blinkTime  500                                   // was 1000

boolean displayFLAG = true;

boolean  bval = false;



// StopWatch
  int OldTime = 0;
  int CurrentTime = 0;
  int TotalTime = 0;

uint8_t SWDigit4 = 0;
uint8_t SWDigit3 = 0;
uint8_t SWDigit2 = 0;
uint8_t SWDigit1 = 0;

int SWMINUTES = 0;
int SWSECONDS = 0;

int dayIndex = 0;


boolean scrollDirFlag = false;


volatile boolean MINUP = false;
volatile boolean MINDOWN = false;
volatile boolean TFH = false;




extern const uint8_t GRAPHIC[][5];
extern const uint8_t logo[][20];
