/**********************************************************************
*	TEST FOR: Small storage Ring Buffer - max storage size of 256 bytes (uint8_t)
*	
*	Author: Joshua Talbot
*	Date: 5-MAR-2015
*	Revision: 1.0
*	Soruce:  https://github.com/talbot-j ... T.B.D. ...
	
	Purpose:
		Test the functionality of the small ring buffer code.  Use/modify 
		this to test any changes to the ByteRingBufferU32L.c, ByteRingBufferU32L.h 
		source files.

	Usage:
		Tested using (on Linux with gcc installed):
			Requires: smBYTE_RB_U32L_TEST.c, ByteRingBufferU32L.c ByteRingBufferU32L.h in same folder.
				Compile, type-> gcc -c smBYTE_RB_U32L_TEST.c ByteRingBufferU32L.c
				Link, type-> gcc -o ByteRingBufferU32L smBYTE_RB_U32L_TEST.o ByteRingBufferU32L.o
				Then execute, type-> ./smBYTE_RB_U32L_TEST

	License:
		Copyright (C) 2015  Joshua Talbot

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "ByteRingBufferU32L.h"

uint8_t data = 0;

void Write_data_in_buffer(BYTE_RB_U32L_T *buf, uint8_t data)
{
	if ( BYTE_RB_Full(buf) != 1 ) {
		printf("Just wrote %d into an available element.\n", data);
		BYTE_RB_Write(buf, data);
	}
	else 
	{
		printf("!!!Buffer FULL!  Dropped data = %d!!!\n", data);
	}
}

void Write_data_in_buffer_wrapping_overflow(BYTE_RB_U32L_T *buf, uint8_t data)
{
	if ( BYTE_RB_Full(buf) != 1 ) {
		printf("Just wrote %d into an available element.\n", data);
		BYTE_RB_Write(buf, data);
	}
	else 
	{
		printf("!!!Buffer Overflowed when writing = %d!!!\n", data);
		BYTE_RB_Write(buf, data);
	}
}

uint8_t Read_data_in_buffer( BYTE_RB_U32L_T *buf )
{
	uint8_t readData = 0;
	if ( BYTE_RB_Empty(buf) != 1 ) {
		readData = BYTE_RB_Read(buf);
		printf("Used \"Read_data_in_buffer\" to read element, data = %d\n", readData);
	}
	else 
	{
		printf("!!!Used \"Read_data_in_buffer\" to read element, but Buffer EMPTY!!!\n");
	}
	return readData;
}

void Test_Block_Write(BYTE_RB_U32L_T *buf, uint32_t block_size, uint8_t data, uint8_t method)
{
	uint32_t idx;

	for ( idx = 0; idx < block_size; idx++ )
	{
		if (method == 1) Write_data_in_buffer( buf, data);
		else (Write_data_in_buffer_wrapping_overflow (buf, data));
		data++;
	}
}

int main ( void )
{
	uint8_t bufferA[11];
	uint8_t bufferB[1204];
	BYTE_RB_U32L_T ringBufferA;
	BYTE_RB_U32L_T ringBufferB;
	BYTE_RB_U32L_T *pRingBuffer;

	uint8_t *pBufferA = bufferA;
	pRingBuffer = &ringBufferA;
	BYTE_RB_Init(pRingBuffer, pBufferA, sizeof(bufferA));

	uint8_t *pBufferB = bufferB;
	pRingBuffer = &ringBufferB;
	BYTE_RB_Init(pRingBuffer, pBufferB, sizeof(bufferB));

	pRingBuffer = &ringBufferA;
	printf("Available space in RingBuffer A: %d\n", BYTE_RB_Avail_Space(pRingBuffer));

	pRingBuffer = &ringBufferB;
	printf("Available space in RingBuffer B: %d\n", BYTE_RB_Avail_Space(pRingBuffer));
	printf("Ring buffer empty? %d\n", BYTE_RB_Empty(pRingBuffer));
	printf("Ring buffer full? %d\n", BYTE_RB_Full(pRingBuffer));
	printf("Ring buffer available space? %u\n", BYTE_RB_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %ud\n", BYTE_RB_Avail_Data(pRingBuffer));

	uint8_t writeNum = 26;
	printf("Using \"Write_data_in_buffer()\" to write %d into an available buffer element.\n", writeNum);
	Write_data_in_buffer(pRingBuffer, writeNum);
	printf("Ring buffer available space? %d\n", BYTE_RB_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %d\n", BYTE_RB_Avail_Data(pRingBuffer));

	uint8_t readNum = Read_data_in_buffer(pRingBuffer);
	if( readNum == writeNum) printf("Read/Write Pairing was a sucess!\n");
	else (printf("Read/Write Pairing FAILED!!!\n"));
	printf("Ring buffer available space? %u\n", BYTE_RB_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %u\n", BYTE_RB_Avail_Data(pRingBuffer));

	writeNum = 1;
	uint32_t block_size = 8;
	printf("Use \"Test_Block_Write()\" to write %d sequencial data starting at value = %d\n", block_size, writeNum);
	Test_Block_Write(pRingBuffer, block_size, writeNum, 1);
	uint32_t idx;
	for ( idx = 0; idx < block_size; idx++)
	{
		Read_data_in_buffer(pRingBuffer);
	}

	writeNum = 100;
	block_size = 1000;
	printf("Use \"Test_Block_Write()\" to write %d sequencial data starting at value = %d\n", block_size, writeNum);
	Test_Block_Write(pRingBuffer, block_size, writeNum, 0);
	printf("Ring buffer available space? %u\n", (uint8_t) BYTE_RB_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %u\n", BYTE_RB_Avail_Data(pRingBuffer));
	for ( idx = 0; idx < block_size; idx++)
	{
		Read_data_in_buffer(pRingBuffer);
	}
	printf("Ring buffer available space? %d\n", BYTE_RB_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %d\n", BYTE_RB_Avail_Data(pRingBuffer));


	/* testing of the "peek" function:
	 	Steps:
	 	Write some various strings to the ring buffer, lets say 0x55 and 0xAA.
	 	We should verify the available data is 2.  The peek should report 
	 	back a 0x55.  The sniff should report back 0xAA.  Then get the avail 
	 	data again and it should still be equal to two.  Now read a byte.  A 
	 	peek and sniff should both return the same value when the available 
	 	data is 1.  Now write and read 12 items*/
	uint8_t buf_data = 0;

	BYTE_RB_Flush( &ringBufferA );

	if ( BYTE_RB_Sniff ( &ringBufferA, &buf_data ) ) {
		printf("Test Fail - Sniff should return false.\n");
	}
	if ( BYTE_RB_Peek ( &ringBufferA, &buf_data ) ) {
		printf("Test Fail - Sniff should return false.\n");
	}
	if ( BYTE_RB_Avail_Data( &ringBufferA ) != 0 ) {
		printf("Test Fail - Buffer should be empty.\n");
		exit(1);
	}
	BYTE_RB_Write( &ringBufferA, 0x55 );
	if ( BYTE_RB_Avail_Data( &ringBufferA ) != 1 ) {
		printf("Test Fail - Buffer should be 1.\n");
		exit(1);
	}
	if ( BYTE_RB_Sniff ( &ringBufferA, &buf_data ) ) {
		printf("buf_data = 0x%X\n", buf_data);
		if ( buf_data != 0x55 ) {
			printf("Test Fail - Sniff should return 0x55.\n");
			exit(1);
		}
	}
	if ( BYTE_RB_Peek ( &ringBufferA, &buf_data ) ) {
		printf("buf_data = 0x%X\n", buf_data);
		if ( buf_data != 0x55 ) {
			printf("Test Fail - Peek should return 0x55.\n");
			exit(1);
		}
	}
	if ( BYTE_RB_Avail_Data( &ringBufferA ) != 1 ) {
		printf("Test Fail - Buffer should be 1.\n");
		exit(1);
	}
	BYTE_RB_Write( &ringBufferA, 0xAA );
	if ( BYTE_RB_Avail_Data( &ringBufferA ) != 2 ) {
		printf("Test Fail - Buffer should be 2.\n");
		exit(1);
	}
	if ( BYTE_RB_Sniff ( &ringBufferA, &buf_data ) ) {
		printf("buf_data = 0x%X\n", buf_data);
		if ( buf_data != 0xAA ) {
			printf("Test Fail - Sniff should return 0xAA.\n");
			exit(1);
		}
	}
	if ( BYTE_RB_Peek ( &ringBufferA, &buf_data ) ) {
		printf("buf_data = 0x%X\n", buf_data);
		if ( buf_data != 0x55 ) {
			printf("Test Fail - Peek should return 0x55.\n");
			exit(1);
		}
	}
	if ( BYTE_RB_Avail_Data( &ringBufferA ) != 2 ) {
		printf("Test Fail - Buffer should be 2.\n");
		exit(1);
	}
	/* test the ability of sniff to wrap around the buffer limits */
	while ( BYTE_RB_Avail_Space( &ringBufferA ) ) {
		BYTE_RB_Write( &ringBufferA, 0x01 );
	}
	
	bufferA[10] = 0x02;
	if ( BYTE_RB_Sniff ( &ringBufferA, &buf_data ) ) {
		printf("buf_data = 0x%X\n", buf_data);
		if ( buf_data != 0x02 ) {
			printf("Test Fail - Sniff should return 0x02.\n");
			exit(1);
		}
	}
	/* test the ability of peek to wrap around the buffer limits */
	while ( BYTE_RB_Avail_Data( &ringBufferA ) != 1 ) {
		BYTE_RB_Read( &ringBufferA );
	}
	if ( BYTE_RB_Peek ( &ringBufferA, &buf_data ) ) {
		printf("buf_data = 0x%X\n", buf_data);
		if ( buf_data != 0x02 ) {
			printf("Test Fail - Peek should return 0x02.\n");
			exit(1);
		}
	}

	return 0;
}