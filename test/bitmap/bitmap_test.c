/*
 * =================================================
 *
 *       Filename:  test/bitmap_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Thu Jan  8 17:02:46 2015
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
#include <unistd.h>

int main(int argc, char** argv){

	initFile("../../build/hd");
	initDiskBuf();
	initSuperBlock();
	initBitMap();
	printBitMap();
	sleep(2);
	releaseBitMap();
	printf("----\n");
	sleep(2);
	
    return 0;
}
