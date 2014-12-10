/*
 * =================================================
 *
 *       Filename:  inode.c
 *
 *    Description: inode 
 *
 *        Version:  0.01
 *        Created:  Wed Dec 10 18:35:55 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */


struct inode
{
	short i_mode;	//文件的类型和属性
	short i_uid;	//文件宿主id
	long i_size;	//文件长度
	long i_mtime;	//修改时间
	char i_gid;		//文件宿主的组id
	char i_nlinks;	//有多少个文件目录项指向该节点
	short i_zone[9];	//文件所占用磁盘块号数组
};


