/*
 * =================================================
 *
 *       Filename:  test/dir_entry/delete_entry_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Fri Jan  9 22:51:46 2015
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
#include "inode.h"
#include "dir_entry.h"

int main(int argc, char** argv){

	initFile("../../build/hd");
	initDiskBuf();
	initSuperBlock();
	initBitMap();
	initRootDir();
	initINode();

	printBitMap();

	_delete_dir_entry("/home/me/a.txt");

	printBitMap();

	printDirInfo();

    return 0;
}
