/*
 * =================================================
 *
 *       Filename:  hd.h
 *
 *    Description: block is a logical block 
 *
 *        Version:  0.01
 *        Created:  Wed Dec 10 20:21:06 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include "config.h"

#ifndef HD_H_HEADER
#define HD_H_HEADER

struct Block
{
	char data[NUM_PHY_LOG][PHYSICAL_BLOCK_SIZE];
};

typedef struct Block blk;

void _read(blk* block,int blockNo);
void _write(blk* block,int blockNo);

void initFile(char* fileName);


#endif
