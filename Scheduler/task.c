#include "task.h"

task* create_task(int nice_input, double execution_time_input, long double weight_calculation) {
	task* new_task = (task*)malloc(sizeof(task));
	if (new_task == NULL) {
		// Handle error
		LOG_ERROR(ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
		exit(EXIT_FAILURE);
	}

	new_task->id = get_id();

	new_task->execution_time = 0;
	new_task->remaining_time = execution_time_input;
	new_task->nice = nice_input;
	new_task->weight = weight_calculation;

	// Default values
	new_task->vruntime = 0;

	char message[STANDART_SIZE_MESS];
	INFO_MESSAGE_CREATED_NEW_TASK(message, new_task->id, new_task->remaining_time, new_task->weight);
	LOG_INFO(message);

	return new_task;
}

void free_task(task* task) {
	if (task == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
		return; // Return instead of freeing NULL pointer
	}
	// Log task freeing
	char mess[STANDART_SIZE_MESS];
	INFO_MESSAGE_FREEING_TASK(mess, task->id);
	LOG_INFO(mess);
	
	free(task);

	task = NULL;
}
