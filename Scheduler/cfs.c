#include "cfs.h"
#include "general_settings.h"
#include "logger.h"
#include "consts.h"


void execute_tree(rb_tree* tasks_tree) {

	// Check if the tasks_tree is NULL and log an error
	if (tasks_tree == NULL) {
		LOG_ERROR(ERROR_MESSAGE_TREE_NOT_INITIALIZED);
		return;
	}

	// Check if the most_left node is NULL and log an error
	if (tasks_tree->most_left == NULL || tasks_tree->most_left->task == NULL) {
		LOG_ERROR(ERROR_MESSAGE_ACCESSING_NULL_POINTER);
		return;
	}

	// Extract task details
	double time_slice = tasks_tree->most_left->task->slice;
	long double weight = tasks_tree->most_left->task->weight;
	long double total_weights = tasks_tree->total_weights;
	double remaining_time = tasks_tree->most_left->task->remaining_time;
	double execution_time = tasks_tree->most_left->task->execution_time;

	// Calculate the time slice based on task weight and total weights
	time_slice = SCHED_LATENCY * (weight / total_weights);
	double delta_exec = time_slice;

	// Determine the sleep time, ensuring it is within the remaining execution time
	double sleep_time = min(max(time_slice, MIN_TIME_SLICE), remaining_time);

	// Log the scheduling details
	char message[STANDART_SIZE_MESS];
	DEBUG_MESSAGE_TASK_SCHEDULED(message, tasks_tree->most_left->task->id, sleep_time);
	LOG_DEBUG(message);

	// Sleep for the determined time
	Sleep((DWORD)sleep_time);

	// Update task times
	tasks_tree->most_left->task->remaining_time -= sleep_time;
	tasks_tree->most_left->task->execution_time += sleep_time;
	rb_node* old_most_left = tasks_tree->most_left;

	// Log the task execution
	INFO_MESSAGE_TASK_GET_CPU(message, old_most_left->task->id, sleep_time);
	LOG_INFO(message);

	//TODO
	//remove node from the tree without deleting from the memory, update the most left leaf

	delete_most_left_leaf(tasks_tree);

	if (remaining_time == 0) {
		tasks_tree->total_weights -= weight;
	}
	else {
		rb_tree_insert_task(tasks_tree, old_most_left);
	}
}
