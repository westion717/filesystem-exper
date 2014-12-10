/*
 * =================================================
 *
 *       Filename:  hd.c
 *
 *    Description: read and write data to txt as a hd 
 *
 *        Version:  0.01
 *        Created:  Wed Dec 10 20:20:37 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "hd.h"

static FILE *fp;

void initFile(char* fileName)
{

	if((fp=fopen(fileName,"r+"))==NULL){
		printf("\nCannot open file strike any key exit!");
		exit(1);
	}
}


void release()
{
	fclose(fp);
}

void _read(blk * block,int blockNo)
{
	char ch;
	int i=0;

	fseek(fp, (blockNo-1)*PHYSICAL_BLOCK_SIZE,SEEK_SET);  
	while((ch=fgetc(fp))!=EOF && i<PHYSICAL_BLOCK_SIZE){
		block->data[i]=ch;
		i++;
	}


}

void _write(blk* block,int blockNo)
{
	int i=0;

	fseek(fp, (blockNo-1)*PHYSICAL_BLOCK_SIZE,SEEK_SET);  
	while(i<PHYSICAL_BLOCK_SIZE){
		fputc(block->data[i],fp);
		i++;
	}
}


