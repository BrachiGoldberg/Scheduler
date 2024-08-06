#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "rb_tree.h"

#define sched_latency 1

typedef struct
{
	rb_tree* tasks_tree;
}scheduler;
#endif // !SCHEDULER_H