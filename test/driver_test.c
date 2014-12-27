/*
 * =================================================
 *
 *       Filename:  driver_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Dec 27 14:41:10 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include<stdio.h>

#include "config.h"
#include "hd.h"

blk block;

int main(int argc, char** argv){

	initFile("./input.txt");

	_read(&block,1);
	for(int i=0;i<PHYSICAL_BLOCK_SIZE;i++)
	block.data[0][i]='a';
	_write(&block,1);

    return 0;
}
