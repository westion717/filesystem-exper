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

int _create_dir_entry(char* name,short i_mode,short i_uid,char i_gid);
short _findINodeByName(char* name);
int _delete_dir_entry(char* name);

#endif
