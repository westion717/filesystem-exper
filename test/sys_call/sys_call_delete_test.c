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
	

	if(delete("/home/Robert/test.ttt")==SUCCESS)
		printf("delete success \n");
	else
		printf("delete error \n");



	stopFS();
	
	

    return 0;
}
