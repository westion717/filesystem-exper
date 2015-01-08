/*
 * =================================================
 *
 *       Filename:  root_entry_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Thu Jan  8 21:05:16 2015
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

int main(int argc, char** argv){

	initFile("../../build/hd");
	initDiskBuf();
	initSuperBlock();
	initBitMap();
	initRootDir();
	
	printDirInfo();




	releaseBitMap();
	
    return 0;
}
