/*
 * =================================================
 *
 *       Filename:  super_test.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Dec 27 14:45:01 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */
#include<stdio.h>
#include "super.h"
#include "hd.h"
#include "buffer.h"

int main(int argc, char** argv){
	initFile("../../build/hd");
	initDiskBuf();
	initSuperBlock();
	printInfo();
    return 0;
}
