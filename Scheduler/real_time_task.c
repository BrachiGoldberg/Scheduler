#include "real_time_task.h"

// Function to create a new real-time task
real_time_task* create_real_time_task(int priority, double execution_time, long double weight) {

	// Allocate memory for the new task
	real_time_task* new_task = (real_time_task*)malloc(sizeof(real_time_task));
	if (new_task == NULL) {
		// Log error and exit if memory allocation fails
		LOG_ERROR(ERROR_MESSAGE_MEMORY_ALLOCATION_FAILED);
		exit(EXIT_FAILURE);
	}

	// Initialize task properties
	new_task->id = get_id();
	new_task->remaining_time = execution_time;
	new_task->execution_time = 0;
	new_task->weight = weight;

	// Log task creation
	char mess[STANDART_SIZE_MESS];
	INFO_MESSAGE_CREATED_NEW_REAL_TIME_TASK(mess, new_task->id, execution_time, weight);
	LOG_INFO(mess);
	return new_task;
}

// Function to free a real-time task
void free_real_time_task(real_time_task* real_time_task) {
	if (real_time_task == NULL) {
		// Log error if attempting to free a NULL pointer
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
		return;
	}

	// Log task freeing
	char mess[STANDART_SIZE_MESS];
	INFO_MESSAGE_FREEING_REAL_TIME_TASK(mess, real_time_task->id);
	LOG_INFO(mess);

	// Free the task memory and avoid dangling pointers
	free(real_time_task);
	real_time_task = NULL;
}
