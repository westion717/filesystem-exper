/*
 * =================================================
 *
 *       Filename:  dir_entry.h
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Wed Dec 31 19:21:24 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#ifndef DIR_ENTRY_H_HEADER
#define DIR_ENTRY_H_HEADER



#define DIR_FULL_ERROR -1
#define NO_DIR_ERROR 1
#define NO_DELETE_ERROR 2
#define ADD_ENTRY_ERROR -2
#define NO_SUCH_ENTRY -3
#define DELETE_ENTRY_ERROR -4



typedef struct DirEntry
{
	char dirName[14];
	short i_node_num;
}dir_entry;


typedef struct DirBuf
{
	dir_entry entrys[LOGICAL_BLOCK_SIZE/16];
	int is_changed;
	unsigned int no;//所在逻辑块编号
	int size;
}dir_buf;




int _create_dir_entry(char* name,short i_mode,short i_uid,char i_gid);
short _findINodeByName(char* name);
int _delete_dir_entry(char* name);
void initRootDir();
void printDirInfo();

#endif
