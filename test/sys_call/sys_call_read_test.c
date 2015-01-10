/*
 * =================================================
 *
 *       Filename:  create_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Jan 10 06:55:07 2015
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include<stdio.h>
#include "init.h"
#include "sys_call.h"


int main(int argc, char** argv){

	initFS();
	
	
	char data[50];

	File* fp = open("/home/me/a.txt","r");
	if(fp==NULL)
	{
		printf("open failed\n");
		return 1;
	}
	int result = read(fp,data,50);

	printf("%d\n",result);
	printf("%s",data);



	stopFS();
	
	

    return 0;
}
