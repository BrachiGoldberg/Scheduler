#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "rb_tree.h"
#include "RealTimeTaskQueue.h"
#include "QueueNode.h"
#include "general_settings.h"
#include "round_robin.h"
#include "cfs.h"
#include "logger.h"
#include "consts.h"
#include <windows.h>
#include <stdio.h>
#include <math.h>
typedef struct
{
    rb_tree* tasks_tree;
    struct real_time_task_queue* queue;
} scheduler;

void new_task_arrival(int nice, double execution_time, scheduler* sched_point);
void scheduling_tasks(scheduler* sched);

DWORD WINAPI input_thread(LPVOID arg);
DWORD WINAPI task_thread(LPVOID arg);

#endif // SCHEDULER_H
