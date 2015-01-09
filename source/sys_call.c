/*
 * =================================================
 *
 *       Filename:  sys_call.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Jan 10 01:30:16 2015
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */



#include "sys_call.h"
#include <stdio.h>

File* open(char* filename,char* mode,short uid)
{
	char temp_mode;
	switch(mode[0])
	{
	 	case 'r':temp_mode=MODE_READ;break;
		case 'w':temp_mode=MODE_WRITE;break;
		default:printf("open mode error\n");
	}

	if(mode[1]=='+')
		temp_mode=MODE_READ_AND_WRITE;
	return	_open_file(filename,temp_mode,uid);
}
