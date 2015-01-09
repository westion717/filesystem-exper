/*
 * =================================================
 *
 *       Filename:  test/fs/open_read_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Jan 10 04:23:32 2015
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include<stdio.h>
#include <string.h>
#include "buffer.h"
#include "hd.h"
#include "super.h"
#include "bitmap.h"
#include "inode.h"
#include "dir_entry.h"
#include "fs.h"

int main(int argc, char** argv){

	initFile("../../build/hd");
	initDiskBuf();
	initSuperBlock();
	initBitMap();
	initRootDir();
	initINode();
	//printBitMap();

	File* fp = _open_file("/home/me/a.txt",MODE_READ,1);

	if(fp!=NULL)
	{
		printf("open success\n");
	}

	char s[50];

	_read_file(fp,s,50,1);

	
	printf("%s",s);
	//releaseBitMap();
	//flushBuff();

    return 0;
}
