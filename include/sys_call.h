/*
 * =================================================
 *
 *       Filename:  include/sys_call.h
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Jan 10 01:31:06 2015
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include "fs.h"

#ifndef SYS_CALL_H_HEADER
#define SYS_CALL_H_HEADER

#define SUCCESS 1
#define ERROR 0


File* open(char* filename,char* mode);
int read(File* fp,void* des,long size);
void close(File* fp);
int create(char* name,char mode);
int delete(char* name);
int my_rename(char*oldName,char* newName);
file_list lsfile(char* name);

int write(File* file,const void* src,long offset,long size);

#endif
