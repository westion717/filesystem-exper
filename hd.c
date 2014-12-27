/*
 * =================================================
 *
 *       Filename:  hd.c
 *
 *    Description: read and write logical block by api in hd_driver.c
 *
 *        Version:  0.01
 *        Created:  Wed Dec 10 20:20:37 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include <stdio.h>
#include "config.h"
#include "hd.h"
#include "hd_driver.h"

void initFile(char* fileName)
{
	_initFile(fileName);
}


void release()
{
	_release();
}

void _read(blk * block,int blockNo)
{

	for(int i=0;i<NUM_PHY_LOG;i++)
	{
		_read_phy_block(block->data[i],blockNo+i);
	}

}

void _write(blk* block,int blockNo)
{
	for(int i=0;i<NUM_PHY_LOG;i++)
	{
		_write_phy_block(block->data[i],blockNo+i);
	}
}


