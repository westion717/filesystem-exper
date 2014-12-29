/*
 * =================================================
 *
 *       Filename:  super.h
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Wed Dec 10 16:11:50 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#ifndef SUPER_H_HEADER
#define SUPER_H_HEADER


struct super
{
	short s_ninodes; //i节点数
	unsigned short s_nzones; //逻辑块数
	short s_imap_blocks; //i节点位图所占块数
	short s_zmap_blocks; //逻辑块位图所占块数
	short s_first_data_zone; //数据区第一个逻辑块块号
	short s_log_zone_size; //log2（磁盘块数/逻辑块）
	long s_max_size; //最大文件长度
	short s_magic; //文件系统幻数(0x137f)
};


void initSuperBlock();
void printInfo();

short get_s_imap_blocks();
short get_s_zmap_blocks();
short get_first_data_zone();
#endif
