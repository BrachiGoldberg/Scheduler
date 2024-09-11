#include "cfs.h"

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

	//lock the tree
	lock_tree_mutex();
	//get the most left leaf and delete it from the tree
	rb_node* most_left = delete_most_left_leaf(tasks_tree);

	long double total_weights = tasks_tree->total_weights;
	//unlock the tree
	release_tree_mutex();

	// Extract task details
	long double weight = most_left->task->weight;
	double remaining_time = most_left->task->remaining_time;
	double execution_time = most_left->task->execution_time;

	// Calculate the time slice based on task weight and total weights
	double time_slice = SCHED_LATENCY * (weight / total_weights);

	// Determine the sleep time, ensuring it is within the remaining execution time
	double sleep_time = min(max(time_slice, MIN_TIME_SLICE), remaining_time);

	// Sleep for the determined time
	Sleep((DWORD)sleep_time);

	//update vruntime
	double vrun = sleep_time * (DEFUALT_WEIGHT / weight);
	most_left->task->vruntime += vrun;

	// Update task times
	most_left->task->remaining_time -= sleep_time;
	most_left->task->execution_time += sleep_time;

	// Log the task execution
	char message[STANDART_SIZE_MESS];
	INFO_MESSAGE_TASK_GET_CPU(message, most_left->task->id, sleep_time);
	LOG_INFO(message);



	if (most_left->task->remaining_time == 0) {

		lock_tree_mutex();
		tasks_tree->total_weights -= weight;
		tasks_tree->num_of_tasks--;
		release_tree_mutex();

		INFO_MESSAGE_TASK_FINISHED(message, most_left->task->id);
		LOG_INFO(message);

		free_rb_node(most_left);

		logger_flush();
	}
	else {
		rb_tree_insert_task(tasks_tree, most_left);
	}
}