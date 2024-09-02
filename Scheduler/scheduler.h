#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "rb_tree.h"
#include "RealTimeTaskQueue.h"

#include "QueueNode.h"
#include "RealTimeTask.c"

#include "general_settings.h"
#include "round_robin.h"
#include "cfs.h"

#include "logger.h"
#include "consts.h"

typedef struct 
{
	rb_tree* tasks_tree;
	struct real_time_task_queue* queue;
}scheduler;

void new_task_arrival(int nice, double execution_time, scheduler* sched_point);

void scheduling_tasks(scheduler* sched);
#endif // !SCHEDULER_H
