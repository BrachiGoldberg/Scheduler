#include "cfs.h"
#include "general_settings.h"

void execute_tree(rb_tree* tasks_tree) {
	double slice = tasks_tree->most_left->task->slice;
	long double weight = tasks_tree->most_left->task->weight;
	long double total_weights = tasks_tree->total_weights;
	double remaining_time = tasks_tree->most_left->task->remaining_time;
	double execution_time = tasks_tree->most_left->task->execution_time;

	slice = SCHED_LATENCY * (weight / total_weights);
	double delta_exec = slice;

	while (remaining_time > 0 && delta_exec < slice)
	{
		//тглеп vruntime
		delta_exec++;
		remaining_time--;
	}

	tasks_tree->most_left->task->execution_time += delta_exec;
	tasks_tree->most_left->task->remaining_time = remaining_time;
	task* t = tasks_tree->most_left->task;
	//remove task from tree, update most left
	
	if (remaining_time == 0) {
		tasks_tree->total_weights -= weight;
	}
	else
	{
		insert_task(tasks_tree, t);
	}
}