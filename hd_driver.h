/*
 * =================================================
 *
 *       Filename:  hd_driver.h
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  Sat Dec 27 14:27:23 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#ifndef HD_DRIVER_HEADER
#define HD_DRIVER_HEADER


void _initFile(char* fileName);

void _release();


void _read_phy_block(char* physical_block,int blockNo);

void _write_phy_block(char* physical_block,int blockNo);
#endif
