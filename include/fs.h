/*
 * =================================================
 *
 *       Filename:  fs.h
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Wed Dec 31 19:00:38 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#ifndef FS_H_HEADER
#define FS_H_HEADER


#define CREATE_FILE_ERROR -1
#define DELETE_FILE_OK 2

short _create_file(short imode,short i_uid,char i_gid);

int _delete_file(unsigned int pos);

#endif
