/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.csource.org/ for more detail.
**/

//storage_dio.h

#ifndef _STORAGE_DIO_H
#define _STORAGE_DIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "tracker_types.h"
#include "fast_task_queue.h"

struct storage_dio_context
{
	struct fast_task_queue queue;
	pthread_mutex_t lock;
	pthread_cond_t cond;
};

struct storage_dio_thread_data
{
	/* for mixed read / write */
	struct storage_dio_context *contexts;
	int count;  //context count

	/* for separated read / write */
	struct storage_dio_context *reader;
	struct storage_dio_context *writer;
};

#ifdef __cplusplus
extern "C" {
#endif

extern int g_dio_thread_count;

int storage_dio_init();
void storage_dio_terminate();

int storage_dio_get_thread_index(struct fast_task_info *pTask, \
		const int store_path_index, const char file_op);
int storage_dio_queue_push(struct fast_task_info *pTask);

int dio_read_file(struct fast_task_info *pTask);
int dio_write_file(struct fast_task_info *pTask);
int dio_delete_file(struct fast_task_info *pTask);
int dio_discard_file(struct fast_task_info *pTask);

void dio_read_finish_clean_up(struct fast_task_info *pTask);
void dio_write_finish_clean_up(struct fast_task_info *pTask);
void dio_append_finish_clean_up(struct fast_task_info *pTask);
void dio_trunk_write_finish_clean_up(struct fast_task_info *pTask);

int dio_check_trunk_file(struct fast_task_info *pTask);
int dio_write_chunk_header(struct fast_task_info *pTask);

#ifdef __cplusplus
}
#endif

#endif

