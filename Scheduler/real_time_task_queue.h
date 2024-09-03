#ifndef REAL_TIME_TASK_QUEUE_H
#define REAL_TIME_TASK_QUEUE_H

#include <stdlib.h>
#include "queue_node.h"
#include "mutex.h"
#include "consts_logs.h"
#include "logger.h"

struct {
	queue_node* front; // Head of queue
	queue_node* rear; // the tail of the queue
	//initialize at 0!!
	long double total_weights; //total_weights fo all the real timr task in thr queue
	int num_of_tasks; //the count for all the real timr task in thr queue
}typedef real_time_task_queue;

void push_task_node(real_time_task_queue* real_time_task_queue, queue_node* real_time_node);
queue_node* pop_task_node(real_time_task_queue* real_time_task_queue);
int is_queue_empty(real_time_task_queue* real_time_task_queue);
real_time_task_queue* initialize_queue();
void free_queue(real_time_task_queue* queue);

#endif
