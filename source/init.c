/*
 * =================================================
 *
 *       Filename:  init.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Dec 27 20:43:28 2014
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

void initFS()
{
	initFile("../../build/hd");
	initDiskBuf();
	initSuperBlock();
	initBitMap();
	initRootDir();
	initINode();
}

void stopFS()
{
	releaseBitMap();
	flushBuff();
}
