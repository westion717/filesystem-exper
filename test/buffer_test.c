/*
 * =================================================
 *
 *       Filename:  test/buffer_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Dec 27 15:56:16 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include<stdio.h>
#include "buffer.h"

#include <time.h>
#include "config.h"
#include "hd.h"

int main(int argc, char** argv){

	initFile("./input.txt");

	initDiskBuf();

	clock_t t1,t2;

	blk blk[11];
	for(int i=0;i<11;i++)
	{
		
		for(int j=0;j<PHYSICAL_BLOCK_SIZE;j++)
			blk[i].data[0][j]='a'+i;
		t1=clock();
		_write_to_buf(&blk[i],i+1);
		t2=clock();
		printf("%ld\n",t2-t1);
	}

    return 0;
}
