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
	
	char* s="This is Robert Wu who is using this\n fucking system\n";
	
	char data[50];

	File* fp = open("/home/me/a.txt","r");
	read(fp,data,50);


	printf("%ld",fp->file_size);
	printf("%s",data);

	//create("/home/Robert",MODE_DIR);


	stopFS();
	
	

    return 0;
}
