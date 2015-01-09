/*
 * =================================================
 *
 *       Filename:  test/dir_entry/find_dir_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Fri Jan  9 16:43:09 2015
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


	short inum=_findINodeByName("/home/me");	
	const struct inode* node=findINode(inum);
	printf("/home/me,mode=%d\n",node->i_mode);
	printf("/home/me,subdir node num=%d\n",node->i_zone[0]);

	short inum1 =_findINodeByName("/home/me/a.txt");	
	const struct inode* node1=findINode(inum1);
	printf("/home/me/a.txt,mode=%d\n",node1->i_mode);
	printf("/home/me/a.txt,=%ld\n",node1->i_size);


	releaseBitMap();
	flushBuff();
    return 0;
}
