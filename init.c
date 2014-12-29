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
#include "super.h"
#include "inode.h"
#include "buffer.h"
#include "hd.h"

void initFS()
{

	initFile("./input.txt");
	initSuperBlock(HD_SIZE);
	initDiskBuf();
	initINode();
}
