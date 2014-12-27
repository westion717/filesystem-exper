/*
 * =================================================
 *
 *       Filename:  super.c
 *
 *    Description:  This is 1.0 file system of minix written
 *    by myself according to Linux 0.11 analysis.
 *
 *        Version:  0.01
 *        Created:  Wed Dec 10 16:11:36 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include "super.h"
#include "config.h"
#include <stdio.h>


struct super
{
	short s_ninodes; //i节点数
	unsigned short s_nzones; //逻辑块数
	short s_imap_blocks; //i节点位图所占块数
	short s_zmap_blocks; //逻辑块位图所占块数
	short s_first_data_zone; //数据区第一个逻辑块块号
	short s_log_zone_size; //log2（磁盘块数/逻辑块）
	long s_max_size; //最大文件长度
	short s_magic; //文件系统幻数(0x137f)
};

static struct super superBlock;

void initSuperBlock()
{
	superBlock.s_nzones=HD_SIZE/LOGICAL_BLOCK_SIZE; //磁盘总大小/逻辑块大小
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
};





void printInfo()
{
	printf("%d\n",superBlock.s_magic);
	printf("%d\n",superBlock.s_ninodes);
	printf("%d\n",superBlock.s_nzones);
	printf("%d\n",superBlock.s_imap_blocks);
	printf("%d\n",superBlock.s_zmap_blocks);
	printf("%d\n",superBlock.s_first_data_zone);
	printf("%d\n",superBlock.s_log_zone_size);
	printf("%ld\n",superBlock.s_max_size);

}






