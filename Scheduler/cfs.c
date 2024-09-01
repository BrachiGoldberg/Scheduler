#include "cfs.h"
#include "general_settings.h"
#include "logger.h"
#include "consts.h"

void execute_tree(rb_tree* tasks_tree) {

	//does it unnecessary??
	/*if (tasks_tree == NULL) {
		LOG_ERROR(TREE_WAS_NOT_INITIALIZED);
		return;
	}*/

	double time_slice = tasks_tree->most_left->task->slice;
	long double weight = tasks_tree->most_left->task->weight;
	long double total_weights = tasks_tree->total_weights;
	double remaining_time = tasks_tree->most_left->task->remaining_time;
	double execution_time = tasks_tree->most_left->task->execution_time;

	time_slice = SCHED_LATENCY * (weight / total_weights);
	double delta_exec = time_slice;

	double sleep_time = min(max(time_slice, MIN_TIME_SLICE), remaining_time);
	sleep(sleep_time);

	tasks_tree->most_left->task->remaining_time -= sleep_time;
	tasks_tree->most_left->task->execution_time += sleep_time;
	task* t = tasks_tree->most_left->task;
	//remove task from tree, update most left

	if (remaining_time == 0) {
		tasks_tree->total_weights -= weight;
	}
	else
	{
		rb_tree_insert_task(tasks_tree, t);
	}
}