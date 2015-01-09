/*
 * =================================================
 *
 *       Filename:  fs.h
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Wed Dec 31 19:00:38 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include "inode.h"

#ifndef FS_H_HEADER
#define FS_H_HEADER

#define MAX_OPEN_NUM 32

#define CREATE_FILE_ERROR -1
#define DELETE_FILE_OK 2
#define TOO_LARGE_FILE -2
#define WRITE_ERROR -3
#define WRITE_SUCCESS 3
#define NO_REASON_ERROR -4


#define MODE_READ 1
#define MODE_WRITE 2
#define MODE_READ_AND_WRITE 3



typedef struct OpenFile
{
	long fid;
	short inode_num;
	short u_id;
	long file_ptr;
	char openmode;
	long file_size;
}File;


short _create_file(short imode,short i_uid,char i_gid);

int _delete_file(unsigned int pos);

int _write_file(struct inode* node,void* src,long offset,long size);

File* _open_file(char* name,char mode,char uid);
int _read_file(File* fp,void* des,long size,short uid);

#endif
