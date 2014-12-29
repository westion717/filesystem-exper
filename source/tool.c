/*
 * =================================================
 *
 *       Filename:  tool.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Dec 27 20:21:02 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include "tool.h"

void my_memcpy(const void * src,void* des,unsigned int size)
{
	const char* s = (const char*)src;
	char* d = (char*)des;
	for(unsigned int i=0;i<size;i++)
	{
		*d++=*s++;
	}
}

