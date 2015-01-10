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
	
	/*file_list f =lsfile("/home");

	printf("size=%d\n",f.size);
	for(int i=0;i<f.size;i++)
	{
		printf("size=%s\n",f.names[i]);
	}*/

	stopFS();
	

    return 0;
}
