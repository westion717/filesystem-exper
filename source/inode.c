/*
 * =================================================
 *
 *       Filename:  inode.c
 *
 *    Description: inode 
 *
 *        Version:  0.01
 *        Created:  Wed Dec 10 18:35:55 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include <stdlib.h>
#include <stdio.h>

#include "buffer.h"
#include "config.h"
#include "super.h"
#include "tool.h"
#include "inode.h"
#include "bitmap.h"


typedef struct inodeBuf
{
	struct inode data[LOGICAL_BLOCK_SIZE/32];
	int is_changed;
	unsigned int no;
}inode_buf;


static inode_buf ibuf;

static void initIBuf();
static int findINodeEntryIndex(unsigned int pos);

static void initIBuf()
{
	unsigned int first_i_block_no=get_s_imap_blocks()+get_s_zmap_blocks()+SUPER_BLOCK_SIZE+1; 
	my_memcpy(_read_from_buf(first_i_block_no)->data,ibuf.data,LOGICAL_BLOCK_SIZE);
	ibuf.no=first_i_block_no;
	ibuf.is_changed=0;
}

void initINode()
{
	initIBuf();
	initBitMap();
}

short insertINode(struct inode* inode)
{
	int pos = findIPos();
	if(pos==BIT_FULL_ERROR)
	{
		printf("inode is full\n");
		return NODE_FULL_ERROR;
	}
	printf("pos=%d\n",pos);
	int index=findINodeEntryIndex(pos);
	ibuf.data[index]=*inode;
	ibuf.is_changed=1;
	return pos;
}

void deleteINode(unsigned int pos)
{
	int index=findINodeEntryIndex(pos);	
	ibuf.data[index].i_mode=MODE_NO_INODE;
	releaseIPos(pos);
	ibuf.is_changed=1;
}

struct inode* findINode(unsigned int pos)
{
	int index=findINodeEntryIndex(pos);	
	return &ibuf.data[index];	
}

static int findINodeEntryIndex(unsigned int pos)
{
	unsigned int tempNo=pos*32/LOGICAL_BLOCK_SIZE+1+get_s_imap_blocks()+get_s_zmap_blocks()+1;
	printf("tempNo=%d\n",tempNo);
	if(ibuf.no!=tempNo)
	{
		if(ibuf.is_changed) 
		{
			blk block; 
			my_memcpy(ibuf.data,block.data,LOGICAL_BLOCK_SIZE);
	 		_write_to_buf(&block,ibuf.no);
		}
	 	my_memcpy( _read_from_buf(tempNo)->data,ibuf.data,LOGICAL_BLOCK_SIZE);
	}
	int index=pos%(LOGICAL_BLOCK_SIZE/32);
	return index; 
}

