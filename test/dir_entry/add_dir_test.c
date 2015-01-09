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


int main(int argc, char** argv){

	initFile("../../build/hd");
	initDiskBuf();
	initSuperBlock();
	initBitMap();
	initRootDir();
	initINode();

	printDirInfo();


	printf("1:preparing for inserting\n");
	_create_dir_entry("/home",MODE_DIR,1,1);
	printf("1:inserted");
	printDirInfo();


	printf("2:preparing for inserting\n");
	_create_dir_entry("/home/me",MODE_DIR,1,1);
	printf("2:inserted");
	printDirInfo();


	printf("3:preparing for inserting\n");
	_create_dir_entry("/home/me/a.txt",MODE_FILE,1,1);
	printf("3:inserted");
	printDirInfo();
	releaseBitMap();

	flushBuff();

	return 0;
}
