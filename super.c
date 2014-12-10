/*
 * =================================================
 *
 *       Filename:  super.c
 *
 *    Description:  This is 1.0 file system of minix written
 *    by myself according to Linux 0.11 analysis.
 *
 *        Version:  0.01
 *        Created:  Wed Dec 10 16:11:36 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */





struct super
{
	short s_ninodes; //i节点数
	short s_nzones; //逻辑块数
	short s_imap_blocks; //i节点位图所占块数
	short s_zmap_blocks; //逻辑块位图所占块数
	short s_first_data_zone; //数据区第一个逻辑块块号
	short s_log_zone_size; //log2（磁盘块数/逻辑块）
	long s_max_size; //最大文件长度
	short s_magic; //文件系统幻数(0x137f)
};






