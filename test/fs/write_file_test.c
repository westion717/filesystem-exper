/*
 * =================================================
 *
 *       Filename:  test/fs/write_file_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Fri Jan  9 23:41:30 2015
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

	printBitMap();

	short i = _findINodeByName("/home/me/a.txt");

	struct inode node = *findINode(i);
	

	char* s="This is a test\n";

	_write_file(&node,s,0,strlen(s));
	modifyINode(i,&node);
	printBitMap();

	printDirInfo();

	releaseBitMap();
	flushBuff();

    return 0;
}
