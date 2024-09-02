#include "task.h"
#include "logger.h"
#include "consts.h"

task* create_task(int nice_input, double execution_time_input, long double weight_calculation) {
	task* new_task = (task*)malloc(sizeof(task));
	if (new_task == NULL) {
		// Handle error
		LOG_ERROR(ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
		exit(1);
	}

	new_task->id = id++;

	new_task->execution_time = 0;
	new_task->remaining_time = execution_time_input;
	new_task->nice = nice_input;
	new_task->weight = weight_calculation;

	// Default values
	new_task->slice = new_task->vruntime = 0;

	return new_task;
}

void free_task(task* task) {
	if (task == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
		return; // Return instead of freeing NULL pointer
	}
	free(task);
	// Optionally set the pointer to NULL if needed, but this does not affect the caller
	task = NULL;
}
