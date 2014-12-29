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

typedef struct BitMap
{
	char* mapArea;
	unsigned int size_byte;
}bit_map;

static bit_map imap;
static bit_map zmap;

static unsigned int findPos(bit_map* map);
static void init(bit_map* map,int logical_block_num);
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
	return -1;//full store 
}

void initBitMap()
{
	init(&imap,get_s_imap_blocks());
	init(&zmap,get_s_zmap_blocks());
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

static void init(bit_map* map,int logical_block_num)
{
	map->size_byte = logical_block_num*LOGICAL_BLOCK_SIZE;
	map->mapArea=(char*)malloc(map->size_byte);
	for(unsigned int i=0;i<map->size_byte;i++)
	{	
		map->mapArea[i]=0;	
	}
	map->mapArea[0]=1;
}
static void release(bit_map* map)
{
	free(map->mapArea);
}
