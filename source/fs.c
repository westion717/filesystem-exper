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
#include "dir_entry.h"
#include <time.h>
#include <stdio.h>



static File openfiles[MAX_OPEN_NUM];

static short write_one_zone(struct inode* node,const blk* block,int zone_num);
static short calLogicalPos(struct inode* node,short zone_num);
static short newAIndexBlock();
static void deleteNormalFile(const struct inode* node);
static const blk* read_one_block(const struct inode* node,int zone_num);

static File* findEmptyPos()
{
	for(int i=0;i<MAX_OPEN_NUM;i++)
	{
		if(openfiles[i].fid==0)
			return &openfiles[i];
	}
	printf("file list is full \n");
	return NULL;
}

File* isInOpenList(short inode_num)
{
	for(int i=0;i<MAX_OPEN_NUM;i++)
	{
		if(openfiles[i].inode_num==inode_num)
			return &openfiles[i];
	}
	return NULL;
}


void _close_file(File *fp)
{
	fp=isInOpenList(fp->inode_num);
	flushBuff();
	fp->fid=0;
}

File* _open_file(char* name,char mode,char uid)
{
	short inode_num = _findINodeByName(name);
	if(inode_num==NO_SUCH_ENTRY)
	{
		printf("no such file\n");
		return NULL;
	}
	File* file=isInOpenList(inode_num);
	if(file!=NULL)
	{
		if(file->openmode==MODE_WRITE || file->openmode==MODE_READ_AND_WRITE){
			printf("file has been opened by other process\n");
			return NULL;
		}
		else
			return file;
	}
	const struct inode* node = findINode(inode_num);

	if(node->i_mode==MODE_DIR)
	{
		printf("can not open dir\n");
		return NULL;
	}

	file = findEmptyPos();
	if(file==NULL)
		return NULL;

	file->openmode=mode;
	file->u_id=uid;
	file->inode_num=inode_num;
	file->fid=time(NULL);
	file->file_size=node->i_size;

	switch(mode)
	{
		default:file->file_ptr=0;break;
	}
	return file;
}

int _read_file(File* fp,void* des,long size,short uid)
{
	if(fp==NULL)
		return 0;
	fp = isInOpenList(fp->inode_num);
	if(fp==NULL)
	{
		printf("the file has not been opened\n");
		return 0;
	}
	if(fp->u_id!=uid)
	{
		printf("the file has been opened by others\n");
		return 0;
	}

	long realSize=0;

	const struct inode* node=findINode(fp->inode_num);

	int zone_num=fp->file_ptr/LOGICAL_BLOCK_SIZE;
	int block_rest = fp->file_ptr%LOGICAL_BLOCK_SIZE;

	if(block_rest!=0)
	{
		const blk *block=read_one_block(node,zone_num);
		if(block==NULL)
		{
			printf("read error\n");
			return 0;
		}
		int restpart=LOGICAL_BLOCK_SIZE-block_rest;
		if(size<restpart)
		{
			my_memcpy((char*)block->data+block_rest,des,size);
			realSize+=size;
			size=0;
		}
		else
		{
			my_memcpy((char*)block->data+block_rest,des,restpart);
			size-=restpart;
			des+=restpart;
			realSize+=restpart;
		}
		zone_num++;
	}

	if(size<=0)
	{
		return realSize;
	}

	const blk *b;
	while(size>0)
	{
		b=read_one_block(node,zone_num);
		if(size<=LOGICAL_BLOCK_SIZE)
		{
			my_memcpy(b->data,des,size);
			realSize+=size;
			break;
		}
		else
		{
			my_memcpy(b->data,des,LOGICAL_BLOCK_SIZE);
			des+=LOGICAL_BLOCK_SIZE;			
			size-=LOGICAL_BLOCK_SIZE;
			realSize+=LOGICAL_BLOCK_SIZE;
			zone_num++;
		}
	}
	return realSize;
}

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
		blk block=*_read_from_buf(calLogicalPos(node,zone_num)+get_first_data_zone());
		int restpart=LOGICAL_BLOCK_SIZE-block_rest;
		if(size<restpart)
		{
			my_memcpy(src,(char*)block.data+block_rest,size);
			size=0;
		}
		else
		{
			my_memcpy(src,(char*)block.data+block_rest,restpart);
			size-=restpart;
			src+=restpart;
		}
		write_one_zone(node,&block,zone_num);
		zone_num++;
	}

	if(size<=0)
	{
		if(node->i_size<offset+size)
			node->i_size=offset+size;
		return WRITE_SUCCESS;
	}

	blk b;
	while(size>0)
	{
		if(size<=LOGICAL_BLOCK_SIZE)
		{
			my_memcpy(src,b.data,size);
			write_one_zone(node,&b,zone_num);
			break;
		}
		else
		{
			my_memcpy(src,b.data,LOGICAL_BLOCK_SIZE);
			src+=LOGICAL_BLOCK_SIZE;			
			size-=LOGICAL_BLOCK_SIZE;
			write_one_zone(node,&b,zone_num);
			zone_num++;
		}
	}
	if(node->i_size<offset+size)
		node->i_size=offset+size;
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
static const blk* read_one_block(const struct inode* node,int zone_num)
{
	const blk* blk = NULL;
	if(zone_num<7)
	{
		if(node->i_zone[zone_num]!=-1){
			blk=_read_from_buf(node->i_zone[zone_num]+get_first_data_zone());


			return blk;
		}
		else
			return NULL;
	}

	zone_num-=7;
	if(zone_num<512)
	{
		if(node->i_zone[7]!=-1)
		{
			blk = _read_from_buf(node->i_zone[7]);
			short index=*((short*)blk->data+zone_num);
			if(index==-1)
				return NULL;
		}
		else
			return NULL;
	}
	zone_num-=512;
	if(node->i_zone[8]!=-1)
	{
		blk = _read_from_buf(node->i_zone[8]);
		short index=*((short*)blk->data+zone_num);
		if(index==-1)
			return NULL;
	}
	else
		return NULL;

	return blk;
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


