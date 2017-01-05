****************************************************************************
Byte Storage Ring Buffer using 32 bit unsigned ints for the buffer size limit.
****************************************************************************
# Intro:
	Byte storage Ring Buffer with a unit32_t max storage buffer size.
 
# Purpose:
     This implements a thread (interrupt safe) ring buffer that utilizes read
     and write counts (see http://en.wikipedia.org/wiki/Circular_buffer) to
     insure that the producer only modifies the write count and the consumer
     only modifies the read count.  Using this insures that any delay in the
     head and tail updates and corrections on them due to overruns is avoided.
     This routine targets the use of byte storage (perfect for serial port
     data transfers) on 32bit targets or in cases where a 8bit or 16bit target
     needs a VERY large buffer.  The SmRingBuffer (the code that this was
     forked from) was written use on a 8 bit machines with maximum buffer
     lengths of 255 bytes.
 
 	## Note:
     This project is fully documented using Doxygen.  Feel free to generate
     the documentation for this project using the DoxyfileV1.0.  Note the be
     sure to change the path of the Dot installation (on line 2362). This is
     not required - only needed to create the call graphs.  You can obtain the
     install for dot binaries by installing Graphviz, found here:
     http://www.graphviz.org/
 
 	Author: Joshua Talbot
 	Date:   5-JAN-2017
 
 	Version 	1.0 - initial Release
 				1.1 - Added the Peek and Sniff functions.
 
# Source:
     https://github.com/talbot-j/smRingBuffer <br>For a brief description and
     usage information see the header file.
 
 # Copyright:

	<b>Copyright (C) 2017  Joshua Talbot</b>

	This program is free software: you can redistribute it and/or modify it under the
	terms of the GNU General Public License as published by the Free
	Software Foundation, either version 3 of the License, or (at your
	option) any later version. This program is distributed in the
	hope that it will be useful, but WITHOUT ANY WARRANTY; without
	even the implied warranty of MERCHANTABILITY or FITNESS FOR A
	PARTICULAR PURPOSE. <br> See the GNU General Public License for
	more details. You should have received a copy of the GNU General
	Public License along with this program. If not, see
	<http://www.gnu.org/licenses/>.

# Usage example:
 
<code>
   uint8_t dataA[1000];
   BYTE_RB_U32L_T bufA;
   BYTE_RB_U32L_T *pBuf;
   uint8_t *pDataA = dataA;
   pBuf = &bufA;
   BYTE_RB_Init(pBuf, pDataA, sizeof(pDataA));
   uint8_t data = 1;
   if ( BYTE_RB_Full(pBuf) != 1 )
   {
     printf("Just wrote %d into an available element.\n", data);
     BYTE_RB_Write(pBuf, data);
   }
   else
   {
     printf("!!!Buffer FULL!  Dropped data = %d!!!\n", data);
   }
   if ( BYTE_RB_Empty(pBuf) != 1 ) {
     data = BYTE_RB_Read(pBuf);
     printf("Used Read_data_in_buffer\" to read element, data = %d\n", data);
   }
   else
   {
     printf("!!!Used Read_data_in_buffer\" to read element, but Buffer EMPTY!!!\n");
   }
 </code>
 