/*
 * =================================================
 *
 *       Filename:  bitmap.h
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Mon Dec 29 17:28:19 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#ifndef BITMAP_H_HEADER
#define BITMAP_H_HEADER

#define BIT_FULL_ERROR -1

void releaseBitMap();
void initBitMap();
void printBitMap();
	
unsigned int findIPos();
unsigned int findZPos();
void releaseIPos(unsigned int bit_pos);
void releaseZPos(unsigned int bit_pos);

#endif
