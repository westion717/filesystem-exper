/*
 * =================================================
 *
 *       Filename:  bitmap.c
 *
 *    Description: manipulation of bitmap of imap and zmap 
 *
 *        Version:  0.01
 *        Created:  Mon Dec 29 17:11:26 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include <stdlib.h>
#include "config.h"
#include "super.h"
#include "tool.h"
#include "bitmap.h"
#include "buffer.h"
#include <stdio.h>

typedef struct BitMap
{
	char* mapArea;
	unsigned int size_byte;
}bit_map;

static bit_map imap;
static bit_map zmap;

static unsigned int findPos(bit_map* map);
static void release_a_bit(bit_map* map,unsigned int bit_pos);
static void init_map(bit_map* map,int from_logical_no,int logical_block_num);
static void release(bit_map* map);



static unsigned int findPos(bit_map* map)
{
	char temp;
	for(unsigned int i=0;i<map->size_byte;i++)
	{
		temp=map->mapArea[i];

		for(int j=0;j<8;j++)
		{
			if(!(temp & (1<<j)))
			{
				map->mapArea[i]|=(1<<j);
				return i*8+j;
			}
		}
	}
	return BIT_FULL_ERROR;//full store 
}

static void release_a_bit(bit_map* map,unsigned int bit_pos)
{
	int index=bit_pos/8;
	char i=bit_pos%7;
	map->mapArea[index]&=(~(1<<i));
}

void initBitMap()
{
	init_map(&imap,2,get_s_imap_blocks());
	init_map(&zmap,2+get_s_imap_blocks(),get_s_zmap_blocks());
}

void releaseBitMap()
{
	release(&imap);
	release(&zmap);
}
unsigned int findIPos()
{
	return findPos(&imap);
}
unsigned int findZPos()
{
	return findPos(&zmap);
}
void releaseIPos(unsigned int bit_pos)
{
	release_a_bit(&imap,bit_pos);
}
void releaseZPos(unsigned int bit_pos)
{
	release_a_bit(&zmap,bit_pos);
}

static void init_map(bit_map* map,int from_logical_no,int logical_block_num)
{
	map->size_byte = logical_block_num*LOGICAL_BLOCK_SIZE;
	map->mapArea=(char*)malloc(map->size_byte);
	const blk *block;
	for(int i=0;i<logical_block_num;i++)
	{
		block=_read_from_buf(from_logical_no+i);
		my_memcpy(block->data,map->mapArea+i*LOGICAL_BLOCK_SIZE,map->size_byte);
	}
}
static void release(bit_map* map)
{
	free(map->mapArea);
}
static void print_bit_map(bit_map* map)
{	
	char temp;
	for(unsigned int i=0;i<map->size_byte;i++)
	{
		temp=map->mapArea[i];
		for(int j=0;j<8;j++)
		{
			printf("%d",(temp>>j)&1);
		}
		printf("\n");
		printf("num=%d\n",i);
	}
}

void printBitMap()
{
	printf("imap:\n");
	print_bit_map(&imap);
	printf("zmap:\n");
	print_bit_map(&zmap);	
}


