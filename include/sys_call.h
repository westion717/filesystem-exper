/*
 * =================================================
 *
 *       Filename:  include/sys_call.h
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Jan 10 01:31:06 2015
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include "fs.h"

#ifndef SYS_CALL_H_HEADER
#define SYS_CALL_H_HEADER



File* open(char* filename,char* mode,short uid);

#endif
