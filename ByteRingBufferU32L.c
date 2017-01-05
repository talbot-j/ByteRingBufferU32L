/**
 * ----------------------------------------------------------------------------
 * @addtogroup LIB_BYTERINGBUFFER_U32 Byte Sized Ring Buffer with massive storage.
 * @{
 * @brief      Byte storage Ring Buffer with a unit32_t max storage buffer size.
 *
 * @file ByteRingBufferU32L.c
 *
 * @author     Joshua Talbot
 *
 * @date       5-JAN-2017
 *
 * @version    1.0 - initial Release
 * @version    1.1 - Added the Peek and Sniff functions.
 *
 *
 * @par Source:  https://github.com/talbot-j/smRingBuffer<br>For a brief description and usage information see the header
 *     file.
 *
 * @copyright  <b>Copyright (C) 2015  Joshua Talbot</b> <br>This program is free
 *             software: you can redistribute it and/or modify it under the
 *             terms of the GNU General Public License as published by the Free
 *             Software Foundation, either version 3 of the License, or (at your
 *             option) any later version. This program is distributed in the
 *             hope that it will be useful, but WITHOUT ANY WARRANTY; without
 *             even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 *             PARTICULAR PURPOSE. <br> See the GNU General Public License for
 *             more details. You should have received a copy of the GNU General
 *             Public License along with this program. If not, see
 *             <http://www.gnu.org/licenses/>.
 */

#include "ByteRingBufferU32L.h"

/*!
 * @brief      BYTE_RB_Init - required to initalize the buffer.
 *
 * @param[in]  buf   - an address which is of type BYTE_RB_U32L_T that requires
 *                   initialization
 * @param[in]  data  - an address of which will hold data for the buffer, must
 *                   be of at least length 'size' (the next parameter).
 * @param[in]  size  - the size of the buffer storage array (or the maximum
 *                   amount allowed to be used from that storage array).
 */
void BYTE_RB_Init ( BYTE_RB_U32L_T *buf, uint8_t *data, uint32_t size)
{
	buf->size = size;
	buf->data = data;
	buf->head = 0;
	buf->tail = 0;
	buf->read_count = 0;
	buf->write_count = 0;
}

/**
 * @brief      Read the next element in the buffer.
 *
 * @param[in]  buf   - pointer to buffer data type
 * @warning    Be sure to check that the buffer is not empty.
 *
 * @return     { description_of_the_return_value }
 */
uint8_t BYTE_RB_Read ( BYTE_RB_U32L_T *buf )
{
	/* read the data from the buffer */
	uint8_t readData = buf->data[buf->tail];
	/* setup for the next read: inc the read count and the tail index */
	buf->read_count++;
	if( ++buf->tail == buf->size) 
		buf->tail =0;
	return readData;
}

/**
 * @brief      write an element into the buffer location.
 *
 * @param[in]  buf   - pointer to buffer data type
 * @param[in]  data  - the data that will be added to the buffer
 * @warning    Be sure to check prior to using this function that the buffer is
 *             not FULL.
 */
void BYTE_RB_Write ( BYTE_RB_U32L_T *buf, uint8_t data )
{
	/* write the data to the buffer */
	buf->data[buf->head] = data;
	/* setup for the next write: inc the write count and the head index */
	buf->write_count++;
	if( ++buf->head == buf->size) 
		buf->head =0;
}

/**
 * @brief      write an element into the buffer location. A pointer is passed to
 *             the value that needs to be added.
 *
 * @param[in]  buf    - pointer to buffer data type
 * @param[in]  pData  - an address which holds the data that will be added to
 *                    the buffer
 * @warning    Be sure to check prior to using this function that the buffer is
 *             not FULL.
 */
void BYTE_RB_pWrite ( BYTE_RB_U32L_T *buf, uint8_t *pData )
{
	/* write the data to the buffer */
	buf->data[buf->head] = *pData;
	/* setup for the next write: inc the write count and the head index */
	buf->write_count++;
	if( ++buf->head == buf->size) 
		buf->head =0;
}

/**
 * @brief      Take a peek at the next byte value to be read by the
 *             BYTE_RBRead function without disturbing the head or tail
 *             pointers.
 *
 * @param      buf    A pointer to the small ring buffer.
 * @param      value  A pointer to the memory location to store the "peeked"
 *                    data.
 *
 * @return     true - if there is valid data to peek at (the write head must be
 *             at least 1 or more bytes away from the read pointer).
 * @return     false - if no valid data is available to peek at.
 */
bool BYTE_RB_Peek ( BYTE_RB_U32L_T *buf, uint8_t *value )
{
	bool valid = false;
	/* if buffer has data then lets peek at the data the return it. */
	if ( !BYTE_RB_Empty(buf) ) {
		*value = buf->data[buf->tail];
		valid = true;
	}
	return valid;
}

/**
 * @brief      Take a look back at the previously stored byte in the buffer
 *             without disturbing the head or tail pointers.
 *
 * @param      buf    A pointer to the small ring buffer.
 * @param      value  A pointer to the memory location to store the "sniffed"
 *                    data.
 *
 * @return     true - if there is valid data to sniff (the write head must be at
 *             least 1 or more bytes away from the read pointer).
 * @return     false - if no valid data is available to sniff.
 */
bool BYTE_RB_Sniff ( BYTE_RB_U32L_T *buf, uint8_t *value )
{
	bool valid = false;
	/* if buffer has data then lets peek at the data the return it. */
	if ( !BYTE_RB_Empty(buf) ) {
		uint32_t headm1;
		if ( buf->head == 0 ) {
			headm1 = buf->size - 1;
		}
		else {
			headm1 = buf->head - 1;
		}
		*value = buf->data[headm1];
		valid = true;
	}
	return valid;
}


/**
 * @brief      flushes all data in the buffer and resets the read/write counts.
 *
 * @param[in]  buf   - pointer to buffer data type
 */
void BYTE_RB_Flush ( BYTE_RB_U32L_T *buf )
{
	buf->head = 0;
	buf->tail = 0;
	buf->read_count = 0;
	buf->write_count = 0;
}

/* @} end of addtogroup LIB_BYTERINGBUFFER_U32 */