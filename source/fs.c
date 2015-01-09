/*
 * =================================================
 *
 *       Filename:  fs.c
 *
 *    Description: the core of file system 
 *
 *        Version:  0.01
 *        Created:  Mon Dec 29 17:07:45 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include "inode.h"
#include "fs.h"
#include "bitmap.h"
#include "buffer.h"
#include "tool.h"
#include "super.h"
#include <time.h>
#include <stdio.h>


static short write_one_zone(struct inode* node,const blk* block,int zone_num);
static short calLogicalPos(struct inode* node,short zone_num);
static short newAIndexBlock();
static void deleteNormalFile(const struct inode* node);

short _create_file(short imode,short i_uid,char i_gid)
{
	struct inode node;
	node.i_uid=i_uid;
	node.i_gid=i_gid;
	node.i_mode=imode;
	node.i_mtime=time(NULL);
	for(int i=0;i<9;i++)
	{
		node.i_zone[i]=-1;
	}
	node.i_nlinks=0;

	switch(imode)
	{
		case MODE_DIR:break;
		case MODE_FILE:
		node.i_size=0;
			break;
		
	}

	short result = insertINode(&node);
	if(result==NODE_FULL_ERROR)
	{
		printf("insert node fail\n");
		return CREATE_FILE_ERROR;
	}
	return result;
}

int _delete_file(unsigned int pos)
{
	const struct inode* node=findINode(pos);
	switch(node->i_mode)
	{
		case MODE_FILE:deleteNormalFile(node);break;
		default:break;
	}
	deleteINode(pos);
	return DELETE_FILE_OK;
}

static void deleteNormalFile(const struct inode* node)
{
	for(int i=0;i<7;i++)
	{
		if(node->i_zone[i]!=-1)
			releaseZPos(node->i_zone[i]);
	}
	for(int i=0;i<2;i++)
	{
		if(node->i_zone[7+i]!=-1)
		{
			const blk* block = _read_from_buf(get_first_data_zone()+node->i_zone[7+i]);
			short* ptr=(short*)block->data;
			for(int j=0;i<LOGICAL_BLOCK_SIZE/2;j++)
			{
				if(*ptr!=-1)
					releaseZPos(*ptr);
			}
			releaseZPos(node->i_zone[7+i]);
		}
	}
}

int _write_file(struct inode* node,void* src,long offset,long size)
{	

	if(offset+size>LOGICAL_BLOCK_SIZE*7+LOGICAL_BLOCK_SIZE*1024)
	{
		printf("too large\n");
		return TOO_LARGE_FILE; 
	}

	int zone_num=offset/LOGICAL_BLOCK_SIZE;
	int block_rest=offset%LOGICAL_BLOCK_SIZE;


	if(block_rest!=0)
	{
		blk block=*_read_from_buf(calLogicalPos(node,zone_num));
		int restpart=LOGICAL_BLOCK_SIZE-block_rest;
		if(size<restpart)
		{
			my_memcpy(src,block.data+block_rest,size);
			size=0;
		}
		else
		{
			my_memcpy(src,block.data+block_rest,restpart);
			size-=restpart;
			src+=restpart;
		}
		write_one_zone(node,&block,zone_num);
		zone_num++;
	}
	if(size<=0)
		return WRITE_SUCCESS;

	while(size>0)
	{
		blk b;
		if(size<=LOGICAL_BLOCK_SIZE)
		{
			my_memcpy(src,b.data,size);
			src+=size;
			break;
		}
		else
		{
			my_memcpy(src,b.data,LOGICAL_BLOCK_SIZE);
			src+=LOGICAL_BLOCK_SIZE;			
			size-=LOGICAL_BLOCK_SIZE;
		}
			write_one_zone(node,&b,zone_num);
	}
	return WRITE_SUCCESS;
}

static short calLogicalPos(struct inode* node,short zone_num)
{
	int temp;
	if(zone_num<7)
	{
		if(node->i_zone[zone_num]==-1)
		{
			short zpos=findZPos();
			if(zpos==BIT_FULL_ERROR)
			{
				printf("calLogicalPos error\n");
				return BIT_FULL_ERROR;
			}
			node->i_zone[zone_num]=zpos;
		}
		return node->i_zone[zone_num];
	}
	zone_num-=7;
	if(zone_num <512)
	{
		temp=7;
	}
	else
	{
		temp=8;
		zone_num-=512;
	}

	if(node->i_zone[temp]==-1)
	{
		short zpos = newAIndexBlock();
		if(zpos==BIT_FULL_ERROR)
		{
			printf("new A index error\n");
			return BIT_FULL_ERROR;
		}
		node->i_zone[temp]=zpos;
	}
	blk tempBlk=*_read_from_buf(node->i_zone[temp]+get_first_data_zone());
	short index = *((short*)tempBlk.data+zone_num);
	if(index==-1)
		index=findZPos();

	if(index==BIT_FULL_ERROR)
	{
		printf("cal error\n");
		return BIT_FULL_ERROR;
	}

	*((short*)tempBlk.data+zone_num)=index;
	_write_to_buf(&tempBlk,node->i_zone[temp]+get_first_data_zone());
	return index;
}

static short write_one_zone(struct inode* node,const blk* block,int zone_num)
{
	short index = calLogicalPos(node,zone_num);
	_write_to_buf(block,index+get_first_data_zone());
	return WRITE_SUCCESS;
}

static short newAIndexBlock()
{
	short z=findZPos();
	if(z==BIT_FULL_ERROR)
		return BIT_FULL_ERROR;
	short num[LOGICAL_BLOCK_SIZE/2];
	_write_to_buf((const blk*)num,z);
	return z; 
}


