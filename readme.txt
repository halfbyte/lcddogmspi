LCDdogmSPI library
------------------

This is my first stab at adopting the Arduino LCD library code for usage with 
the EA DOG-M display series, especially in SPI mode (as it is, pincount wise the most desirable mode)

It is tested with an EA DOGM163 display and should (in theory) also work with 
the 081 and the 162 types, but I'd need the hardware to verify this (So feel free to send me the displays :)

Compatibility
-------------
The library has been developed under Arduino011.

Installation
------------
Simply unpack the ZIP inside your libraries folder (The folder location seems to vary heavily from system to system...). After restarting the Arduino Software, you should be able to import the Library into your Sketch.

Usage
-----

Software
--------

See examples.

CAUTION: 

Please note that this implementation currently thinks it is the only one in 
the world using the SPI lines, as it doesn't preserve the state of the SPI
control registers nor does it care for any other CS lines beeing low.
Using this in conjunction with other SPI devices might require some additional
work on your behalf.



Wiring it up
------------

DISPLAY    < - >   ARDUINO
--------------------------
SI           -     11 (MOSI)
CLK          -     13 (SPI-Clock)
RS           -     <rs_pin> (2nd parameter to the library initializer)
CSB          -     <csb_pin> (3rd parameter to the library initializer)
+5V          -     5V (O RLY?)
GND          -     GND (YAH, RLY)

That makes 6 impressive pins for driving a real LCD display. Plus, CLK and SI
are still usable for other SPI devices.

License
-------

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
