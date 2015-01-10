/*
 * =================================================
 *
 *       Filename:  sys_call.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Jan 10 01:30:16 2015
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */



#include "sys_call.h"
#include "env.h"
#include <stdio.h>
#include <time.h>

File* open(char* filename,char* mode)
{
	char temp_mode;
	switch(mode[0])
	{
		case 'r':temp_mode=MODE_READ;break;
		case 'w':temp_mode=MODE_WRITE;break;
		default:printf("open mode error\n");
	}

	if(mode[1]=='+')
		temp_mode=MODE_READ_AND_WRITE;
	return	_open_file(filename,temp_mode,getUid());
}
int read(File* fp,void* des,long size)
{
	return _read_file(fp,des,size,getUid());
}
void close(File* fp)
{
	_close_file(fp);
}



int my_rename(char*oldName,char* newName)
{
	short i = _findINodeByName(oldName);
	File* fp = isInOpenList(i);	
	if(fp!=NULL)
	{
		printf("the file is open ,you can not rename\n");
		return RENAME_ERROR; 
	}
	if(_renameFile(oldName,newName)!=RENAME_OK)
		return ERROR;
	return SUCCESS;
}

int write(File* fp,const void* src,long offset,long size)
{
	fp=isInOpenList(fp->inode_num);
	if(fp==NULL)
	{
		printf("write error without opening");
	}

	struct inode node= *findINode(fp->inode_num);

	long realSize=_write_file(&node,src,offset,size);

	modifyINode(fp->inode_num,&node);

	return realSize;
}


int delete(char* name)
{
	short i = _findINodeByName(name);
	const struct inode* node=findINode(i);
	if(node->i_mode==MODE_DIR)
	{
		if(!isEmpty(name))
		{
			printf("This is not a empty dir\n");
			return 0;
		}
	}
	File* fp = isInOpenList(i);	
	if(fp!=NULL)
	{
		printf("the file is open ,you can not delete\n");
		return 0; 
	}
	if(_delete_dir_entry(name)==NO_DELETE_ERROR)
		return SUCCESS;
	else
		return ERROR;
}

int create(char* name,char mode)
{
	if(_findINodeByName(name)!=NO_SUCH_ENTRY)
	{
		printf("you have same name file or dir\n");
		return 0;
	}
	if(_create_dir_entry(name,mode,getUid(),getGid())==NO_DIR_ERROR)
	{
		return time(NULL);
	}
	return 0;
}


file_list lsfile(char* name)
{
	file_list f = _lsfile(name);
	if(f.size==-1)
		printf("list error\n");
	return f;
	
}
