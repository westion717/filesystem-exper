/*
 * =================================================
 *
 *       Filename:  dir_entry.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Tue Dec 30 22:30:26 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include "buffer.h"
#include "config.h"
#include "super.h"
#include "tool.h"
#include "bitmap.h"
#include "fs.h"
#include "inode.h"
#include "dir_entry.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>




static dir_buf dirBuf;

static void readDirBuf(int logical_block_num);
static int findEntryByName(char* name);
static char* moveToDir(char* name);
static int find_entry();
static void flushDirBuf();

static int find_entry()
{
	for(int i=0;i<LOGICAL_BLOCK_SIZE/16;i++)
	{
		if(dirBuf.entrys[i].i_node_num==-1)
			return i;
	}
	return DIR_FULL_ERROR;
}

int _create_dir_entry(char* name,short i_mode,short i_uid,char i_gid)
{
	char* lastName=moveToDir(name);
	
	if(lastName==NULL)
	{
		printf("no such dir for %s\n",name);
		return ADD_ENTRY_ERROR;
	}
 	int pos=find_entry();
	if(pos==DIR_FULL_ERROR)
	{
	 	printf("create fail;dir is full\n");
		return DIR_FULL_ERROR;
	}
	short ipos=_create_file(i_mode,i_uid,i_gid);
	if(ipos==CREATE_FILE_ERROR)
	{
 		printf("create dir failed;insert node wrong");
		return ADD_ENTRY_ERROR;
	}
	struct inode node=*findINode(ipos);
	short blk_num;
	switch(i_mode)
	{
		case MODE_DIR:
				blk_num=(short)findZPos();
				if(blk_num==BIT_FULL_ERROR)
				{
					deleteINode(ipos);
					printf("logical is full");
					return NO_DIR_ERROR; 
				}

				dir_entry entrys[LOGICAL_BLOCK_SIZE/16];
				for(int i=0;i<LOGICAL_BLOCK_SIZE/16;i++)
				{
				entrys[i].i_node_num=-1;
				strcpy(entrys[i].dirName,"");
				}

				_write_to_buf((const blk*)entrys,blk_num+get_first_data_zone());
				node.i_zone[0]=blk_num;
				modifyINode(ipos,&node);
				break;
		case MODE_FILE:break;
		default:printf("imode error\n");break;
	}
	dirBuf.entrys[pos].i_node_num=ipos;
	strcpy(dirBuf.entrys[pos].dirName,lastName);
	dirBuf.is_changed=1;
	flushDirBuf();
	return NO_DIR_ERROR;
}

int _delete_dir_entry(char* name)
{
	moveToDir(name);
	char* last = strrchr(name,'/');
	int index = findEntryByName(last+1);
	if(index==NO_SUCH_ENTRY)
	{
		printf("no such file\n");
		return NO_SUCH_ENTRY;
	}

	if(_delete_file(dirBuf.entrys[index].i_node_num)==DELETE_FILE_OK)
	{
		dirBuf.entrys[index].i_node_num=-1;
		dirBuf.is_changed=1;
		flushDirBuf();
		return NO_DELETE_ERROR; 
	}
	printf("unknown delete dir error\n");
		return DELETE_ENTRY_ERROR;
}

static char* moveToDir(char* name)
{
	readDirBuf(get_first_data_zone());
	char* temp1;
	char* temp2;
	temp1 = strchr(name,'/');
	if(temp1==NULL)
		return name;
	temp1++;
	temp2 = strchr(temp1,'/');
	char tempName[14];
	while(temp2!=NULL)
	{	
	 	my_memcpy(temp1,tempName,temp2-temp1);
		tempName[temp2-temp1]='\0';
		int index = findEntryByName(tempName);
		if(index==NO_SUCH_ENTRY)
		{
			printf("no such entry\n");
			return NULL;
		}
		const struct inode* node = findINode(dirBuf.entrys[index].i_node_num);
		readDirBuf(node->i_zone[0]+get_first_data_zone());
		temp1=temp2+1;
		temp2=strchr(temp1,'/');
	}
	char* last = strrchr(name,'/');
	last+=1;
	return last;
}

static void flushDirBuf()
{
	if(dirBuf.is_changed==1)
	{
		_write_to_buf((const blk*)dirBuf.entrys,dirBuf.no);
	}
}

short _findINodeByName(char* name)
{
	char* lastName=moveToDir(name);
	if(lastName==NULL)
	{
		printf("no such dir for %s\n",name);
		return NO_SUCH_ENTRY;
	}
	int index = findEntryByName(lastName);
	if(index==NO_SUCH_ENTRY)
	{
		printf("no such file\n");
		return NO_SUCH_ENTRY;
	}
	return dirBuf.entrys[index].i_node_num;
}


static int findEntryByName(char* name)
{
	for(int i=0;i<dirBuf.size;i++)
	{
		if(dirBuf.entrys[i].i_node_num!=-1&&strcmp(dirBuf.entrys[i].dirName,name)==0)
		{
		printf("equal 1=%s,2=%s\n",name,dirBuf.entrys[i].dirName);
			return i;
		}
	}
	return NO_SUCH_ENTRY;
}

static void readDirBuf(int logical_block_num)
{
	if(dirBuf.no==(unsigned int)logical_block_num)
		return;
	if(dirBuf.is_changed==1)
	{
		blk tempBlock;
		my_memcpy(dirBuf.entrys,tempBlock.data,LOGICAL_BLOCK_SIZE);
		_write_to_buf(&tempBlock,dirBuf.no);
	}
	const blk *block = _read_from_buf(logical_block_num);
	my_memcpy(block->data,dirBuf.entrys,LOGICAL_BLOCK_SIZE);
	dirBuf.no=logical_block_num;
	dirBuf.is_changed=0;
	dirBuf.size=LOGICAL_BLOCK_SIZE/16;
}

void initRootDir()
{
	dirBuf.is_changed=0;
	readDirBuf(get_first_data_zone());
}

void printDirInfo()
{
	printf("dir list:\n");
	for(int i=0;i<dirBuf.size;i++)
	{
		printf("inode_num=%d,",dirBuf.entrys[i].i_node_num);
		printf("dirname=%s\n",dirBuf.entrys[i].dirName);
	}
}


