#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "rb_tree.h"
#include "RealTimeTaskQueue .h"
#include "general_settings.h"
#include "round_robin.h"
#include "cfs.h"

typedef struct
{
	struct real_time_task_queue* queue;
	struct rb_tree* tasks_tree;
}scheduler;


void scheduling_tasks(scheduler* sched);
#endif // !SCHEDULER_H