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


#ifndef LCDdogmSPI_h
#define LCDdogmSPI_h

#include <inttypes.h>

class LCDdogmSPI {
	
private:
  int cs_pin, rs_pin, lines;
  
  void spiTransfer(volatile char data);
  
public:
  LCDdogmSPI(int num_lines, int chip_select_pin, int register_select_pin);
  void commandWrite(char value);
  void dataWrite(char value);
  void init();
  void print(char value);
  void println(char value[]);
  void clear();
  //non-core---------------
  void cursorTo(int line_num, int x);
  // void leftScroll(int chars, int delay_time);
  //end of non-core--------

};

#endif
