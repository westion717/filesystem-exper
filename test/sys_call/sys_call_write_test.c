/*
 * =================================================
 *
 *       Filename:  sys_call_create_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Jan 10 12:12:30 2015
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include<stdio.h>
#include "init.h"
#include "sys_call.h"
#include "string.h"


int main(int argc, char** argv){

	initFS();
	
	char* s="11123123123213131312312dsfsdfsdfs";

	if(create("/home/Robert/test.ttt",MODE_FILE)>0)
	{
		printf("create success\n");
	}
	else
		printf("create error\n");

	file_list files=lsfile("/home/Robert");

	printf("size=%d\n",files.size);
	for(int i=0;i<files.size;i++)
	{
		printf("name=%s\n",files.names[i]);
	}


	File *f = open("/home/Robert/test.ttt","w");

	write(f,s,0,strlen(s)+1);

	stopFS();
	

    return 0;
}
