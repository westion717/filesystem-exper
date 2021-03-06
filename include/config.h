/*
 * =================================================
 *
 *       Filename:  config.h
 *
 *    Description: configuration of hd 
 *
 *        Version:  0.01
 *        Created:  Wed Dec 10 18:45:18 2014
 *         Author:  westion, westion717@gmail.com
 *        Company:  ZJUT
 *
 * =================================================
 */

#define HD_SIZE 40000000
#define LOGICAL_BLOCK_SIZE 1024
#define PHYSICAL_BLOCK_SIZE 1024

#define NUM_PHY_LOG LOGICAL_BLOCK_SIZE/PHYSICAL_BLOCK_SIZE

#define IMAP_BLOCK_SIZE 2
#define ZMAP_BLOCK_SIZE 2
#define SUPER_BLOCK_SIZE 1

#define BUFFER_SIZE 10

