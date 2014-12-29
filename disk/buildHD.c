/*
 * =================================================
 *
 *       Filename:  buildHD.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Thu Jan  8 15:51:34 2015
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include<stdio.h>
#include <stdlib.h>
#include "super.h"
#include "config.h"

static struct super superBlock;
static void writeSuper(long capacity);

int main(int argc, char** argv){

	FILE* fp;

	printf("%s",argv[1]);

	if((fp=fopen(argv[1],"w+"))==NULL){
		printf("\nCannot open file strike any key exit!");
		exit(1);
	}
	printf("please input hd size\n");
	long size;
	scanf("%ld",&size);
	char m=-1;
	for(long i=0;i<size;i++)
	{
		fwrite(&m,1,1,fp);
	}
	fseek(fp,0,SEEK_SET);
	writeSuper(size);
	fwrite(&superBlock,sizeof(struct super),1,fp);
	char t=0;
	fseek(fp,LOGICAL_BLOCK_SIZE,SEEK_SET);
	for(int i=0;i<ZMAP_BLOCK_SIZE*LOGICAL_BLOCK_SIZE;i++)
	{
		fwrite(&t,1,1,fp);
	}
	for(int i=0;i<IMAP_BLOCK_SIZE*LOGICAL_BLOCK_SIZE;i++)
	{
		fwrite(&t,1,1,fp);
	}

    return 0;
}

static void writeSuper(long capacity)
{
	superBlock.s_nzones=capacity/LOGICAL_BLOCK_SIZE; //磁盘总大小/逻辑块大小
	superBlock.s_magic=0x137f;
	superBlock.s_imap_blocks=IMAP_BLOCK_SIZE;
	superBlock.s_zmap_blocks=ZMAP_BLOCK_SIZE;
	
	//如果inode不是占整除个逻辑块，则+1补齐块

	int inum = (superBlock.s_imap_blocks*LOGICAL_BLOCK_SIZE*8-1)*32/LOGICAL_BLOCK_SIZE;

if((superBlock.s_imap_blocks*LOGICAL_BLOCK_SIZE*8-1)*32%LOGICAL_BLOCK_SIZE!=0)
	inum++;

	superBlock.s_first_data_zone=inum+superBlock.s_zmap_blocks+superBlock.s_imap_blocks+1+1+1;	//数据区第一个逻辑块数=inum+逻辑位图块数+i节点位图块数+引导块+超级快+1
	superBlock.s_ninodes=IMAP_BLOCK_SIZE*LOGICAL_BLOCK_SIZE*8-1;
	superBlock.s_log_zone_size=0;
	superBlock.s_max_size=(512*512+512+7)*LOGICAL_BLOCK_SIZE;
}
