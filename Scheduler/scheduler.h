#ifndef SCHEDULER_H
#define SCHEDULER_H

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "rb_tree.h"
#include "real_time_task_queue.h"
#include "queue_node.h"
#include "general_settings.h"
#include "round_robin.h"
#include "cfs.h"
#include "logger.h"
#include "logger.h"
#include "consts_logs.h"


typedef struct
{
	rb_tree* tasks_tree;
	real_time_task_queue* queue;
} scheduler;

HANDLE wake_event;

void new_task_arrival(int nice, double execution_time, scheduler* sched_point);
void scheduling_tasks(scheduler* sched);

DWORD WINAPI input_thread(LPVOID arg);
DWORD WINAPI task_thread(LPVOID arg);

void initial_all_structs(scheduler* sched);
void create_input_thread(HANDLE* thread_name, scheduler* sched);
void create_task_thread(HANDLE* thread_name, scheduler* sched);


#endif // SCHEDULER_H
