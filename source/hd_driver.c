/*
 * =================================================
 *
 *       Filename:  hd_driver.c
 *
 *    Description: read and write physical data to txt as a real disk 
 *
 *        Version:  0.01
 *        Created:  Sat Dec 27 14:19:28 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include<stdio.h>
#include <stdlib.h>
#include "config.h"

static FILE *fp;

void _initFile(char* fileName)
{

	if((fp=fopen(fileName,"r+"))==NULL){
		printf("\nCannot open file strike any key exit!");
		exit(1);
	}
}


void _release()
{
	fclose(fp);
}

void _read_phy_block(char* physical_block,int phy_block_no)
{

	fseek(fp, (phy_block_no-1)*PHYSICAL_BLOCK_SIZE,SEEK_SET);  
	fread(physical_block,PHYSICAL_BLOCK_SIZE,1,fp);
	if(ferror(fp))
	{
		printf("read error");
	}

}


void _write_phy_block(char* physical_block,int phy_block_no)
{
	fseek(fp, (phy_block_no-1)*PHYSICAL_BLOCK_SIZE,SEEK_SET);  
	fwrite(physical_block,PHYSICAL_BLOCK_SIZE,1,fp);
	if(ferror(fp))
	{
		printf("write error");
	}

}


