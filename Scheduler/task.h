#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include "logger.h"
#include "consts_logs.h"
#include "general_settings.h"

typedef struct {
	int id;
	int nice;
	long double weight;
	double vruntime;
	double execution_time;
	double remaining_time;
}task;

//static int id;

task* create_task(int nice_input, double execution_time_input, long double weight_calculation);
void free_task(task* task);


#endif // !TASK_H

