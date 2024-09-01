
#include <math.h>
#include "RealTimeTask.h"
#include "consts.h"
#include "logger.h"

struct real_time_task* create_real_time_task(int priority, double execution_time, long double weight) {
	ID++;
	struct real_time_task* new_task = (struct real_time_task*)malloc(sizeof(struct real_time_task));
	if (new_task == NULL) {
		//memory allocation failed
		LOG_ERROR(MEMORY_ALLOCATION_FAILED);
		/// ????? exit(1)
	}

	new_task->id = ID;
	new_task->remaining_time = execution_time;
	new_task->weight = weight;
	return new_task;
}

void free_real_time_task(struct real_time_task* real_time_task) {

	if (real_time_task == NULL) {
		//null pointer
		LOG_ERROR(ACCESSING_NULL_PIONTER);
	}
	else
		free(real_time_task);
}