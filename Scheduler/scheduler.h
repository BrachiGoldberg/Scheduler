#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "rb_tree.h"
#include "RealTimeTaskQueue .h"
#include "QueueNode.h"
#include "RealTimeTask.c"

#define sched_latency 1

typedef struct 
{
	rb_tree* tasks_tree;
	struct real_time_task_queue* queue;
}scheduler;

void new_task_arrival(int nice, double execution_time, scheduler* sched_point);
void scheduling_task();
#endif // !SCHEDULER_H