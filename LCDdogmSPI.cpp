/*
  LCDdogmSPI.h - LCD display library for EA DOG-M displays used by SPI
  Copyright (c) 2008 Jan Krutisch.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


/* 
  Please note that this implementation currently thinks it is the only one in 
  the world using the SPI lines, as it doesn't preserve the state of the SPI
  control registers nor does it care for any other CS lines beeing low.
  Using this in conjunction with other SPI devices might require some additional
  work on your behalf.
*/

#include "LCDdogmSPI.h"

extern "C" {
  #include <stdio.h>  //not needed yet
  #include <string.h> //needed for strlen()
  #include <inttypes.h>
  #include "WConstants.h"  //all things wiring / arduino
}


#define SPI_MOSI_PIN 11
#define SPI_CLK_PIN 13

// define command bytes for the LCD
#define LCDCMD_CLR 1
#define LCDCMD_HOME 2
#define LCDCMD_ON 0x0C
#define LCDCMD_FUN_REG_2 49
#define LCDCMD_FUN_REG_1 48
#define LCDCMD_BIAS_SET 28
#define LCDCMD_POWER_CTL 90
#define LCDCMD_FOLLOWER_CTL 105
#define LCDCMD_CONTRAST_SET 116
#define LCDCMD_ENTRY_MODE_SET 6
#define LCDCMD_SET_DDRAM_ADDRESS 0x80

LCDdogmSPI::LCDdogmSPI(int num_lines, int chip_select_pin, int register_select_pin) {
  cs_pin = chip_select_pin;
  rs_pin = register_select_pin;
  lines = num_lines;
}

void LCDdogmSPI::init() {
  char clr;
  char linesreg;
  pinMode(SPI_MOSI_PIN, OUTPUT);
  pinMode(SPI_CLK_PIN,OUTPUT);
  pinMode(cs_pin,OUTPUT);
  pinMode(rs_pin,OUTPUT);
  
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
  clr=SPSR;
  clr=SPDR;
  delay(50);
  
  linesreg = (lines == 2) ? 8 : 0;
  
  commandWrite(LCDCMD_FUN_REG_2 | linesreg); //function set
  delay(1);
  commandWrite(LCDCMD_FUN_REG_2 | linesreg); //function set
  delay(1);
  commandWrite(LCDCMD_BIAS_SET);
  commandWrite(LCDCMD_POWER_CTL);
  commandWrite(LCDCMD_FOLLOWER_CTL);
  commandWrite(LCDCMD_CONTRAST_SET);
  commandWrite(LCDCMD_ON);
  commandWrite(LCDCMD_CLR); 
  commandWrite(LCDCMD_ENTRY_MODE_SET);
  commandWrite(LCDCMD_HOME);
}

void LCDdogmSPI::commandWrite(char value) {
  digitalWrite(cs_pin,LOW);
  digitalWrite(rs_pin, LOW);
  spiTransfer(value);
  digitalWrite(cs_pin,HIGH);
  delay(60);
}

void LCDdogmSPI::dataWrite(char value) {
  digitalWrite(cs_pin,LOW);
  digitalWrite(rs_pin, HIGH);
  spiTransfer(value);
  digitalWrite(cs_pin,HIGH);
}

// for compatibility with other LCD libs
void LCDdogmSPI::print(char value) {
  dataWrite(value);
}

void LCDdogmSPI::println(char msg[]) {
  uint8_t i;  //fancy int.  avoids compiler warning when comparing i with strlen()'s uint8_t
  for (i=0;i < strlen(msg);i++){
    print(msg[i]);
  }
}

void LCDdogmSPI::clear() {
  commandWrite(LCDCMD_CLR);
}

void LCDdogmSPI::cursorTo(int line_num, int x) {
  char address = 0;
  if (line_num > lines) line_num = lines;
  if (lines == 1) {
    x = x % 8;
  } else {
    x = x % 16;
  }
  address = (lines == 3) ? (line_num * 0x10) : (line_num * 0x40);
  address += x;
  address = address & 0x7F;
  commandWrite(LCDCMD_SET_DDRAM_ADDRESS | address);
}


void LCDdogmSPI::spiTransfer(volatile char data)
{
  SPDR = data;                    // Start the transmission
  while (!(SPSR & (1<<SPIF)));    // Wait for the end of the transmission
}
