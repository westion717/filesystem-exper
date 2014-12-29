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
#include "super.h"
#include <time.h>
#include <stdio.h>


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
		case MODE_FILE:break;
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
	struct inode* node=findINode(pos);
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
	for(int i=0;i<6;i++)
	{
		if(node->i_zone[i]!=-1)
			releaseZPos(node->i_zone[i]);
	}
	for(int i=0;i<3;i++)
	{
		if(node->i_zone[6+i]!=-1)
		{
			const blk* block = _read_from_buf(get_first_data_zone()+node->i_zone[6+i]);
			short* ptr=(short*)block->data;
			for(int j=0;i<LOGICAL_BLOCK_SIZE/2;j++)
			{
				if(*ptr!=-1)
					releaseZPos(*ptr);
			}
			releaseZPos(node->i_zone[6+i]);
		}
	}
}

