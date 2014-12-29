/*
 * =================================================
 *
 *       Filename:  inode_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Dec 27 20:43:00 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include <stdio.h>
#include "init.h"
#include "inode.h"

int main(int argc, char** argv){

	initFS();


	struct inode i={8,1001,1000,10000,(char)1000,(char)2,{1,2,3}};


	for(int j=0;j<50;j++)
	insertINode(i);
	insertINode(i);


    return 0;
}
