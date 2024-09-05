#ifndef REAL_TIME_TASK_H
#define REAL_TIME_TASK_H

#include <math.h>
#include <stdlib.h>
#include "consts_logs.h"
#include "logger.h"
#include "general_settings.h"

struct {
	long id;
	// int priority;               
	double quantum;
	long double weight;
	double remaining_time;
	double execution_time;
}typedef real_time_task;

real_time_task* create_real_time_task(int priority, double execution_time, long double weight);
void free_real_time_task(real_time_task* task);

#endif // REAL_TIME_TASK_H
