/*
 * =================================================
 *
 *       Filename:  buffer.c
 *
 *    Description: This is the buffer for I/O of disk 
 *
 *        Version:  0.01
 *        Created:  Sat Dec 27 14:58:07 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include<stdio.h>
#include "buffer.h"
#include "config.h"

typedef struct buf
{
	int blk_size;
	blk blks[BUFFER_SIZE];
	int blk_pos[BUFFER_SIZE];

}disk_buffer;


static disk_buffer buf;

static int findPos(int blockNo);
static int replaceOne();
static int findEmptyPos();

void initDiskBuf()
{
	buf.blk_size=BUFFER_SIZE;
	for(int i=0;i<BUFFER_SIZE;i++)
	{
		buf.blks[i].is_changed=0;
		buf.blk_pos[i]=-1;
	}
}

static int findPos(int blockNo)
{
	for(int i=0;i<BUFFER_SIZE;i++)
	{
		if(buf.blk_pos[i]==blockNo)
			return i;
	}
	return -1;
}

static int findEmptyPos()
{
	for(int i=0;i<BUFFER_SIZE;i++)
	{
		if(buf.blk_pos[i]==-1)
			return i;
	}

	return replaceOne();
}

static int replaceOne()
{
	if(buf.blks[0].is_changed==1)
	{
		_write(&buf.blks[0],buf.blk_pos[0]);
	}	
	return 0;
}

const blk* _read_from_buf(int blockNo)
{
	int pos;
	pos=findPos(blockNo);
	if(pos==-1)
	{
		pos=findEmptyPos();
		_read(&buf.blks[pos],blockNo);
 		buf.blk_pos[pos]=blockNo;
		buf.blks[pos].is_changed=0;
	}
 	return &buf.blks[pos];
}

void _write_to_buf(const blk* block,int blockNo)
{
	int pos;
	pos=findPos(blockNo);
	if(pos==-1)
	{
		pos=findEmptyPos();
		buf.blk_pos[pos]=blockNo;
	}
	buf.blks[pos]=*block;
 	buf.blks[pos].is_changed=1;
}

void flushBuff()
{
	for(int i=0;i<buf.blk_size;i++)
	{
		if(buf.blk_pos[i]>0 && buf.blks[i].is_changed==1)
			_write(&buf.blks[i],buf.blk_pos[i]);
	}
}



