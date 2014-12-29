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
#include "buffer.h"
#include "tool.h"

static struct super superBlock;

void initSuperBlock()
{
	const blk* block=_read_from_buf(1);
	my_memcpy(block->data,&superBlock,sizeof(struct super));		
};

const struct super* getSuper()
{
	return &superBlock;
}

short get_s_imap_blocks()
{
	return superBlock.s_imap_blocks;
}

short get_s_zmap_blocks()
{
	return superBlock.s_zmap_blocks;
}


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


short get_first_data_zone()
{
	return superBlock.s_first_data_zone;
}





