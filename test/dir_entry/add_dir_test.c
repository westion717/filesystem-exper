/*
 * =================================================
 *
 *       Filename:  add_dir_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Thu Jan  8 21:28:23 2015
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include<stdio.h>
#include "buffer.h"
#include "hd.h"
#include "super.h"
#include "bitmap.h"
#include "dir_entry.h"
#include "inode.h"
#include "inode.h"


int main(int argc, char** argv){

	initFile("../../build/hd");
	initDiskBuf();
	initSuperBlock();
	initBitMap();
	initRootDir();
	initINode();

	printDirInfo();


	printf("preparing for inserting");

	_create_dir_entry("myname",MODE_DIR,1,1);

	printf("inserted");
	printDirInfo();


	releaseBitMap();

	return 0;
}
