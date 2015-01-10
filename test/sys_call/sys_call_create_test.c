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


int main(int argc, char** argv){

	initFS();
	
	char* s="This is Robert Wu who is using this\n fucking system\n";

	if(create("/home/Robert",MODE_DIR)>0)
	{
		printf("create success\n");
	}
	else
		printf("create error\n");


	stopFS();
	
	

    return 0;
}
