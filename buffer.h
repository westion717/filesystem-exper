/*
 * =================================================
 *
 *       Filename:  buffer.h
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Dec 27 15:52:19 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#include "hd.h" 

#ifndef BUFFER_H_HEADER
#define BUFFER_H_HEADER

void initDiskBuf();
const blk* _read_from_buf(int blockNo);
void _write_to_buf(const blk* block,int blockNo);

#endif
